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

#include <iostream>

#include "main-window.hpp"
#include "notebook-hosts.hpp"
#include "status-bar.hpp"
#include "host-select-dialog.hpp"
#include "about-dialog.hpp"
#include "controller.hpp"

#include "config.h"
#include "debug.hpp"


//MainWindow::MainWindow(){
MainWindow::MainWindow(BaseObjectType * cobject, const RefPtrBuilder & refBuilder):
	Gtk::Window(cobject),
	_refPtrBuilder(refBuilder)
{
/*
	 // Load the Glade file
#ifdef GLIBMM_EXCEPTIONS_ENABLED
	try {
		_refPtrBuilder = Gtk::Builder::create_from_file(GLADE_FILE);
	}
	catch(const Glib::FileError& exception) {
		std::cerr << "FileError: " << exception.what() << std::endl;
		throw;
	}
	catch(const Gtk::BuilderError& exception){
		std::cerr << "BuilderError: " << exception.what() << std::endl;
		throw;
	}
#else
	std::auto_ptr<Glib::Error> error;
	_refPtrBuilder = Gtk::Builder::create_from_file(GLADE_FILE, "", "", error);
	if (error.get()){
		std::cerr << error->what() << std::endl;
		return 1;
	}
#endif //GLIBMM_EXCEPTIONS_ENABLED
*/
	// Initiate glade widgets for main window
//	_refPtrBuilder->reparent_widget("main_window-vbox", *this);
//	_refPtrBuilder->get_widget("main_window-vbox", (MainWindow*)*this);
	
	// Get a controller instance that will be used for initialize and connect 
	// signals to members
	Controller& controller = Controller::instance();
	
	// Connect signal handlers for the main window "menu file" items:
/*	_refPtrBuilder->get_widget("imagemenuitem_new", _pImageMenuItemNew);
	if (_pImageMenuItemNew){
		_pImageMenuItemNew->signal_activate().connect( sigc::mem_fun( *this, 
																&MainWindow::on_menuitem_quit_activated) );
	}
	_refPtrBuilder->get_widget("imagemenuitem_quit", _pImageMenuItemOpenFile);
	if (_pImageMenuItemOpenFile){
		_pImageMenuItemOpenFile->signal_activate().connect( sigc::mem_fun( *this, 
																&MainWindow::on_menuitem_quit_activated) );
	}
	_refPtrBuilder->get_widget("imagemenuitem_quit", _pImageMenuItemSave);
	if (_pImageMenuItemSave){
		_pImageMenuItemSave->signal_activate().connect( sigc::mem_fun( *this, 
																&MainWindow::on_menuitem_quit_activated) );
	}
	_refPtrBuilder->get_widget("imagemenuitem_quit", _pImageMenuItemSaveAs);
	if (_pImageMenuItemSaveAs){
		_pImageMenuItemSaveAs->signal_activate().connect( sigc::mem_fun( *this, 
																&MainWindow::on_menuitem_quit_activated) );
	}
*/	 
	_refPtrBuilder->get_widget("imagemenuitem_quit", _pImageMenuItemQuit);
	if (_pImageMenuItemQuit){
		_pImageMenuItemQuit->signal_activate().connect( sigc::mem_fun( *this, 
																&MainWindow::on_imagemenuitem_quit_activated) );
	}


	//Connect signal handlers for the main window "menu edit" items:
	_refPtrBuilder->get_widget("imagemenuitem_cut", _pImageMenuItemCut);
	if (_pImageMenuItemCut){
		_pImageMenuItemCut->signal_activate().connect( sigc::mem_fun( *this, 
																&MainWindow::on_imagemenuitem_cut_activated) );
	}
	_refPtrBuilder->get_widget("imagemenuitem_copy", _pImageMenuItemCopy);
	if (_pImageMenuItemCopy){
		_pImageMenuItemCopy->signal_activate().connect( sigc::mem_fun( *this, 
																&MainWindow::on_imagemenuitem_copy_activated) );
	}
	_refPtrBuilder->get_widget("imagemenuitem_paste", _pImageMenuItemPaste);
	if (_pImageMenuItemPaste){
		_pImageMenuItemPaste->signal_activate().connect( sigc::mem_fun( *this, 
																&MainWindow::on_imagemenuitem_paste_activated) );
	}
	_refPtrBuilder->get_widget("imagemenuitem_delete", _pImageMenuItemDelete);
	if (_pImageMenuItemDelete){
		_pImageMenuItemDelete->signal_activate().connect( sigc::mem_fun( *this, 
																&MainWindow::on_imagemenuitem_delete_activated) );
	}

	
	//Connect signal handlers for the main window "menu view" items:
	_pCheckMenuItemViewToolbar = NULL;
	_refPtrBuilder->get_widget("checkmenuitem_viewtoolbar", _pCheckMenuItemViewToolbar);
	if (_pCheckMenuItemViewToolbar){ 
		_pCheckMenuItemViewToolbar->signal_toggled().connect( sigc::mem_fun( *this, 
							                                                 &MainWindow::on_checkmenuitem_viewtoolbar_toggled) );
	}
	_pCheckMenuItemViewDebug = NULL;
	_refPtrBuilder->get_widget("checkmenuitem_viewdebug", _pCheckMenuItemViewDebug);
	if (_pCheckMenuItemViewDebug){ 
		_pCheckMenuItemViewDebug->signal_toggled().connect( sigc::mem_fun( *this, 
							                                                &MainWindow::on_checkmenuitem_viewdebug_toggled) );
	}


	//Connect signal handlers for the main window "menu help" items:
	_pImageMenuItemAbout = NULL;
	_refPtrBuilder->get_widget("imagemenuitem_about", _pImageMenuItemAbout);
	if (_pImageMenuItemAbout){
		_pImageMenuItemAbout->signal_activate().connect( sigc::mem_fun( *this, 
																	    &MainWindow::on_imagemenuitem_about_activated) );
	}


	//Main Window -> Toolbar
	_refPtrBuilder->get_widget("main_window-toolbar", _pToolbar);
	if (_pToolbar){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}	
	_refPtrBuilder->get_widget("toolbutton_select", _pToolButton_Select);
	if (_pToolButton_Select){
		_pToolButton_Select->signal_clicked().connect( sigc::mem_fun(*this,	
																   &MainWindow::on_clicked_toolbar_select) );
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}	
	_refPtrBuilder->get_widget("toolbutton_connect", _pToolButton_Connect);
	if (_pToolButton_Connect){
		_pToolButton_Connect->signal_clicked().connect( sigc::mem_fun(*this,	
																	  &MainWindow::on_clicked_toolbar_connect) );
		//Signal to controller when present host have been selected for connection
		_pToolButton_Connect->signal_clicked().connect( sigc::mem_fun(controller,	
																	  &Controller::action_host_connect) );

	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}	
	_refPtrBuilder->get_widget("toolbutton_synchronize", _pToolButton_Synchronize);
	if (_pToolButton_Synchronize){
		_pToolButton_Synchronize->signal_clicked().connect( sigc::mem_fun(*this,	
																		  &MainWindow::on_clicked_toolbar_synchronize) );
		//Signal to controller when present host have been selected for synchonization
		_pToolButton_Synchronize->signal_clicked().connect( sigc::mem_fun(controller,	
																		  &Controller::action_host_synchronize) );
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}	


	//Main Window -> (Important stuff)
	_refPtrBuilder->get_widget_derived("main_window-notebook_hosts", _pNotebookHosts);
	if (_pNotebookHosts){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}
	_refPtrBuilder->get_widget_derived("main_window-statusbar", _pStatusBar);
	if (_pStatusBar){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}
//	_ContextId = _pStatusBar->get_context_id("glkm app");


	//Host selection Dialog
	_refPtrBuilder->get_widget_derived("host_select_dialog", _pHostSelectDialog);
	if (_pHostSelectDialog){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}

	//About Dialog
	_refPtrBuilder->get_widget_derived("about_dialog", _pAboutDialog);
	if (_pAboutDialog){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}
#ifdef DEBUG
	//Debug space
	extern TextViewDebug*	pDebug;
	_refPtrBuilder->get_widget_derived("textview_debug", pDebug);
	if (pDebug){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}
	_refPtrBuilder->get_widget("debug_window", _pWindowDebug);
	if (_pWindowDebug){
		_pWindowDebug->signal_delete_event().connect( sigc::mem_fun(*this, &MainWindow::window_debug_on_delete_event));
		_pWindowDebug->show();
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}
#endif // DEBUG

	controller.set__pMainWindow(this);
	controller.init_host_added();
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

void MainWindow::on_checkmenuitem_viewdebug_toggled() {
	if (_pCheckMenuItemViewDebug->get_active()){
		_pWindowDebug->show();
		PRINTD("on_checkmenuitem_viewdebug_toggled active");
	} else {
		_pWindowDebug->hide();
		PRINTD("on_checkmenuitem_viewdebug_toggled inactive");
	}
}

void MainWindow::on_imagemenuitem_about_activated(){
	PRINTD("on_imagemenuitem_about_activated");
	// if use Gtk::Window::present then Gtk::Widget::show is redundant 
	// (more on gtkmm doc)
	//	_pHostSelectDialog->show();
	_pAboutDialog->present();
}


void MainWindow::on_clicked_toolbar_select(){
	PRINTD("on_clicked_toolbar_select");

	// if use Gtk::Window::present then Gtk::Widget::show is redundant 
	// (more on gtkmm doc)
	//	_pHostSelectDialog->show();
	_pHostSelectDialog->present();
}

void MainWindow::on_clicked_toolbar_connect() {
	PRINTD("on_clicked_toolbar_connect");
}

void MainWindow::on_clicked_toolbar_synchronize(){
	PRINTD("on_clicked_toolbar_synchronize");
}


bool  MainWindow::window_debug_on_delete_event(GdkEventAny * g) {
	_pCheckMenuItemViewDebug->set_active(false);
	PRINTD("window_debug_on_delete_event");
    return true;
}
