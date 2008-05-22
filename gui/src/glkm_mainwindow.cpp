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

#include "glkm_mainwindow.hpp"
#include "glkm_treeviewhost.hpp"
#include "glkm_statusbar.hpp"
#include "glkm_aboutdialog.hpp"


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
	_pMenuItemQuit = NULL;
	_refGlademmXml->get_widget("imagemenuitem_quit", _pMenuItemQuit);
	if (_pMenuItemQuit){
		_pMenuItemQuit->signal_activate().connect( sigc::mem_fun( *this, 
																&MainWindow::on_menuitem_quit_activated) );
	}
	//Connect signal handlers for the main window "menu edit" items:
	//TODO
	
	//Connect signal handlers for the main window "menu view" items:
	_pMenuItemViewToolbar = NULL;
	_refGlademmXml->get_widget("checkmenuitem_viewtoolbar", _pMenuItemViewToolbar);
	if (_pMenuItemViewToolbar){ 
		_pMenuItemViewToolbar->signal_toggled().connect( sigc::mem_fun( *this, 
							&MainWindow::on_menuitem_viewtoolbar_toggled) );
	}
	//Connect signal handlers for the main window "menu help" items:
	_pMenuItemAbout = NULL;
	_refGlademmXml->get_widget("imagemenuitem_about", _pMenuItemAbout);
	if (_pMenuItemAbout){
		_pMenuItemAbout->signal_activate().connect( sigc::mem_fun( *this, 
							&MainWindow::on_menuitem_about_activated) );
	}


	//Main Window -> Toolbar
	_refGlademmXml->get_widget("toolbar_mainwindow", _pToolbar);
	if (_pToolbar){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}	
	_refGlademmXml->get_widget("button_connect", _pToolButton_Connect);
	if (_pToolButton_Connect){
		_pToolButton_Connect->signal_clicked().connect( sigc::mem_fun(*this,	
																   &MainWindow::on_clicked_toolbar_connect) );
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}	
	_refGlademmXml->get_widget("button_connect", _pToolButton_Refresh);
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
	_refGlademmXml->get_widget_derived("glkm_aboutdialog", _pAboutDialog);
	if (_pAboutDialog){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}

}

MainWindow::~MainWindow(){
	//Null
}

void MainWindow::on_menuitem_quit_activated(){
	PRINTD("menu quit activated");
	hide();
}

void MainWindow::on_menuitem_viewtoolbar_toggled(){
	if (_pMenuItemViewToolbar->get_active()){
		_pToolbar->show();
		PRINTD("menu viewtoolbar activated");
	} else {
		_pToolbar->hide();
		PRINTD("menu viewtoolbar deactivated");
	}
}

void MainWindow::on_menuitem_about_activated(){
	PRINTD("menu about activated");
	_pAboutDialog->show();
	  //Bring it to the front, in case it was already shown:
	_pAboutDialog->present();
}

void MainWindow::on_clicked_toolbar_connect(){
	_pStatusBar->pop_item(_ContextId);
	_pStatusBar->push_item(_ContextId);
}


void MainWindow::on_clicked_toolbar_refresh(){
	//update current host
}
