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

#include "glkm_mainwindow.hpp"
//#include <libglademm/xml.h>
#include <iostream>
//#include <gtkmm.h>


GlkmMainWindow::GlkmMainWindow()
{
		//Load the Glade file 
#ifdef GLIBMM_EXCEPTIONS_ENABLED
	try
	{
		m_refGlademmXml = Gnome::Glade::Xml::create(GLADE_FILE);
	}
	catch(const Gnome::Glade::XmlError& exception)
    {
		std::cerr << exception.what() << std::endl;
		throw; 
	}	
#else
	std::auto_ptr<Gnome::Glade::XmlError> error;
	m_refGlademmXml = Gnome::Glade::Xml::create(GLADE_FILE, "", "", error);
	if (error.get())
	{
		std::cerr << error->what() << std::endl;
		return 1;
	}
#endif

	//Initiate glade widgets for main window
	m_refGlademmXml->reparent_widget("vbox_mainwindow", *this);


	//Connect signal handlers for the main window "menu file" items:
	pMenuItemQuit = NULL;
	m_refGlademmXml->get_widget("menuitem_quit", pMenuItemQuit);
	if (pMenuItemQuit){
		pMenuItemQuit->signal_activate().connect( sigc::mem_fun( *this, 
																									&GlkmMainWindow::on_menuitem_quit_activated) );
	}
	//Connect signal handlers for the main window "menu edit" items:
	//TODO
	
	//Connect signal handlers for the main window "menu view" items:
	pMenuItemViewToolbar = NULL;
	m_refGlademmXml->get_widget("menuitem_viewtoolbar", pMenuItemViewToolbar);
	if (pMenuItemViewToolbar){ 
		pMenuItemViewToolbar->signal_toggled().connect( sigc::mem_fun( *this, 
																	  											&GlkmMainWindow::on_menuitem_viewtoolbar_toggled) );
	}
	//Connect signal handlers for the main window "menu help" items:
	pMenuItemAbout = NULL;
	m_refGlademmXml->get_widget("menuitem_about", pMenuItemAbout);
	if (pMenuItemAbout){
		pMenuItemAbout->signal_activate().connect( sigc::mem_fun( *this, 
																 										&GlkmMainWindow::on_menuitem_about_activated) );
	}


	//Main Window -> Toolbar
	m_refGlademmXml->get_widget("toolbar_mainwindow", mp_toolbar_mainwindow);
	if (mp_toolbar_mainwindow){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}	
	m_refGlademmXml->get_widget("button_connect", mp_button_connect);
	if (mp_button_connect){
		mp_button_connect->signal_clicked().connect( sigc::mem_fun( *this, 
																  											&GlkmMainWindow::on_clicked_toolbar_connect) );
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}	
	//Main Window -> Tree View
	m_refGlademmXml->get_widget_derived("treeview_process", pGlkmTreeViewProcess);
	if (pGlkmTreeViewProcess){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}
	//Main Window -> Status Bar
	m_refGlademmXml->get_widget_derived("statusbar_mainwindow", pGlkmStatusBar);
	if (pGlkmStatusBar){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}
	m_ContextId = pGlkmStatusBar->get_context_id("glkm app");


	//About Dialog
	m_refGlademmXml->get_widget_derived("glkm_aboutdialog", pGlkmAboutDialog);
	if (pGlkmAboutDialog){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}

}

GlkmMainWindow::~GlkmMainWindow()
{
	//Null
}

void GlkmMainWindow::on_menuitem_quit_activated()
{
	std::cout << "menu quit activated" << std::endl;
	hide();
}

void GlkmMainWindow::on_menuitem_viewtoolbar_toggled()
{
	if (pMenuItemViewToolbar->get_active()){
		mp_toolbar_mainwindow->show();		
		std::cout << "menu viewtoolbar activated" << std::endl;
	} else {
		mp_toolbar_mainwindow->hide();
		std::cout << "menu viewtoolbar deactivated" << std::endl;
	}
}

void GlkmMainWindow::on_menuitem_about_activated()
{
	std::cout << "menu about activated" << std::endl;
	pGlkmAboutDialog->show();
	  //Bring it to the front, in case it was already shown:
	pGlkmAboutDialog->present();
}

void GlkmMainWindow::on_clicked_toolbar_connect()
{
	pGlkmStatusBar->pop_item(m_ContextId);
	pGlkmStatusBar->push_item(m_ContextId);
}
