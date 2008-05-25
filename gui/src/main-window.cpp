/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * gui
 * Copyright (C) Enrique García Álvarez 2007 <kike+glkm@eldemonionegro.com>
 * 
 * gui is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gui is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtkmm/imagemenuitem.h>
#include <gtkmm/checkmenuitem.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/toolbar.h>

#include <iostream>
#include "debug.hpp"

#include "main-window.hpp"
#include "tree-view-host.hpp"
#include "status-bar.hpp"
#include "about-dialog.hpp"
#include "host-select-dialog.hpp"

/* For testing propose use the local (not installed) glade file */
//#define GLADE_FILE  PACKAGE_DATA_DIR "/glkm/glade/glkm.glade" 
#define GLADE_FILE  "/home/enrgar/svn/pfc/trunk/gui/data/glkm.glade" 


MainWindow::MainWindow(){
		//Load the Glade file 
#ifdef GLIBMM_EXCEPTIONS_ENABLED
	try
	{
		_refGlademmXml = Gnome::Glade::Xml::create(GLADE_FILE);
	}
	catch(const Gnome::Glade::XmlError& exception)
    {
		std::cerr << exception.what() << std::endl;
		throw; 
	}	
#else
	std::auto_ptr<Gnome::Glade::XmlError> error;
	_refGlademmXml = Gnome::Glade::Xml::create(GLADE_FILE, "", "", error);
	if (error.get())
	{
		std::cerr << error->what() << std::endl;
		return 1;
	}
#endif

	//Initiate glade widgets for main window
	_refGlademmXml->reparent_widget("vbox_mainwindow", *this);


	//Connect signal handlers for the main window "menu file" items:
/*	_refGlademmXml->get_widget("imagemenuitem_new", _pImageMenuItemNew);
	if (_pImageMenuItemNew){
		_pImageMenuItemNew->signal_activate().connect( sigc::mem_fun( *this, 
																&MainWindow::on_menuitem_quit_activated) );
	}
	_refGlademmXml->get_widget("imagemenuitem_quit", _pImageMenuItemOpenFile);
	if (_pImageMenuItemOpenFile){
		_pImageMenuItemOpenFile->signal_activate().connect( sigc::mem_fun( *this, 
																&MainWindow::on_menuitem_quit_activated) );
	}
	_refGlademmXml->get_widget("imagemenuitem_quit", _pImageMenuItemSave);
	if (_pImageMenuItemSave){
		_pImageMenuItemSave->signal_activate().connect( sigc::mem_fun( *this, 
																&MainWindow::on_menuitem_quit_activated) );
	}
	_refGlademmXml->get_widget("imagemenuitem_quit", _pImageMenuItemSaveAs);
	if (_pImageMenuItemSaveAs){
		_pImageMenuItemSaveAs->signal_activate().connect( sigc::mem_fun( *this, 
																&MainWindow::on_menuitem_quit_activated) );
	}
*/	 
	_refGlademmXml->get_widget("imagemenuitem_quit", _pImageMenuItemQuit);
	if (_pImageMenuItemQuit){
		_pImageMenuItemQuit->signal_activate().connect( sigc::mem_fun( *this, 
																&MainWindow::on_imagemenuitem_quit_activated) );
	}

	//Connect signal handlers for the main window "menu edit" items:
	_refGlademmXml->get_widget("imagemenuitem_cut", _pImageMenuItemCut);
	if (_pImageMenuItemCut){
		_pImageMenuItemCut->signal_activate().connect( sigc::mem_fun( *this, 
																&MainWindow::on_imagemenuitem_cut_activated) );
	}
	_refGlademmXml->get_widget("imagemenuitem_copy", _pImageMenuItemCopy);
	if (_pImageMenuItemCopy){
		_pImageMenuItemCopy->signal_activate().connect( sigc::mem_fun( *this, 
																&MainWindow::on_imagemenuitem_copy_activated) );
	}
	_refGlademmXml->get_widget("imagemenuitem_paste", _pImageMenuItemPaste);
	if (_pImageMenuItemPaste){
		_pImageMenuItemPaste->signal_activate().connect( sigc::mem_fun( *this, 
																&MainWindow::on_imagemenuitem_paste_activated) );
	}
	_refGlademmXml->get_widget("imagemenuitem_delete", _pImageMenuItemDelete);
	if (_pImageMenuItemDelete){
		_pImageMenuItemDelete->signal_activate().connect( sigc::mem_fun( *this, 
																&MainWindow::on_imagemenuitem_delete_activated) );
	}

	
	//Connect signal handlers for the main window "menu view" items:
	_pCheckMenuItemViewToolbar = NULL;
	_refGlademmXml->get_widget("checkmenuitem_viewtoolbar", _pCheckMenuItemViewToolbar);
	if (_pCheckMenuItemViewToolbar){ 
		_pCheckMenuItemViewToolbar->signal_toggled().connect( sigc::mem_fun( *this, 
							&MainWindow::on_checkmenuitem_viewtoolbar_toggled) );
	}
	//Connect signal handlers for the main window "menu help" items:
	_pImageMenuItemAbout = NULL;
	_refGlademmXml->get_widget("imagemenuitem_about", _pImageMenuItemAbout);
	if (_pImageMenuItemAbout){
		_pImageMenuItemAbout->signal_activate().connect( sigc::mem_fun( *this, 
							&MainWindow::on_imagemenuitem_about_activated) );
	}


	//Main Window -> Toolbar
	_refGlademmXml->get_widget("toolbar_mainwindow", _pToolbar);
	if (_pToolbar){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}	
	_refGlademmXml->get_widget("toolbutton_connect", _pToolButton_Connect);
	if (_pToolButton_Connect){
		_pToolButton_Connect->signal_clicked().connect( sigc::mem_fun(*this,	
																   &MainWindow::on_clicked_toolbar_connect) );
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}	
	_refGlademmXml->get_widget("toolbutton_refresh", _pToolButton_Refresh);
	if (_pToolButton_Refresh){
		_pToolButton_Connect->signal_clicked().connect( sigc::mem_fun(*this,	
																   &MainWindow::on_clicked_toolbar_refresh) );
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}	

	//Main Window -> Tree View
	_refGlademmXml->get_widget_derived("treeview_host", _pTreeViewHost);
	if (_pTreeViewHost){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}
#ifdef DEBUG
	//Main Window -> Debug Text View
	extern TextViewDebug*	pDebug;
	_refGlademmXml->get_widget_derived("textview_debug", pDebug);
	if (pDebug){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}
#endif // DEBUG		
	//Main Window -> Status Bar
	_refGlademmXml->get_widget_derived("statusbar_mainwindow", _pStatusBar);
	if (_pStatusBar){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}
	_ContextId = _pStatusBar->get_context_id("glkm app");


	//About Dialog
	_refGlademmXml->get_widget_derived("about_dialog", _pAboutDialog);
	if (_pAboutDialog){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}
	//Host selection Dialog
	_refGlademmXml->get_widget_derived("host_select_dialog", _pHostSelectDialog);
	if (_pHostSelectDialog){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}

}

MainWindow::~MainWindow(){
	//Null
}

void MainWindow::on_imagemenuitem_quit_activated() {
	PRINTD("on_imagemenuitem_quit_activated");
	hide();
}

void MainWindow::on_imagemenuitem_cut_activated() {
	PRINTD("on_imagemenuitem_cut_activated");
}

void MainWindow::on_imagemenuitem_copy_activated() {
	PRINTD("on_imagemenuitem_copy_activated");
}

void MainWindow::on_imagemenuitem_paste_activated() {
	PRINTD("on_imagemenuitem_paste_activated");
}

void MainWindow::on_imagemenuitem_delete_activated() {
	PRINTD("on_imagemenuitem_delete_activated");
}

void MainWindow::on_checkmenuitem_viewtoolbar_toggled() {
	if (_pCheckMenuItemViewToolbar->get_active()){
		_pToolbar->show();
		PRINTD("on_checkmenuitem_viewtoolbar_toggled active");
	} else {
		_pToolbar->hide();
		PRINTD("on_checkmenuitem_viewtoolbar_toggled inactive");
	}
}

void MainWindow::on_imagemenuitem_about_activated(){
	PRINTD("on_imagemenuitem_about_activated");
	_pAboutDialog->show();
	  //Bring it to the front, in case it was already shown:
	_pAboutDialog->present();
}

void MainWindow::on_clicked_toolbar_connect(){
	PRINTD("on_clicked_toolbar_connect");
	_pHostSelectDialog->show();
	//Bring it to the front, in case it was already shown:
	_pHostSelectDialog->present();
}


void MainWindow::on_clicked_toolbar_refresh(){
	PRINTD("on_clicked_toolbar_refresh");
	//update current host
//	_pStatusBar->pop_item(_ContextId);
//	_pStatusBar->push_item(_ContextId);
}

