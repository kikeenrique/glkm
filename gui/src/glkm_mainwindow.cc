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
	try
	{
		m_refGlademmXml = Gnome::Glade::Xml::create(GLADE_FILE);
	}
	catch(const Gnome::Glade::XmlError& exception)
    {
		std::cerr << exception.what() << std::endl;
		throw; 
	}	

	//Initiate glade widgets for main window
	m_refGlademmXml->reparent_widget("vbox_mainwindow", *this);

	//About Dialog  		
	m_refGlademmXml->get_widget_derived("glkm_aboutdialog", pGlkmAboutDialog);
	if(pGlkmAboutDialog){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}


	//Connect signal handlers for the main window "menu file" items:
	pMenuItemQuit = NULL;
	m_refGlademmXml->get_widget("menuitem_quit", pMenuItemQuit);
	if(pMenuItemQuit){
		pMenuItemQuit->signal_activate().connect( sigc::mem_fun( *this, &GlkmMainWindow::on_menuitem_quit_activated) );
	}
	//Connect signal handlers for the main window "menu edit" items:

	//Connect signal handlers for the main window "menu view" items:
	pMenuItemViewToolbar = NULL;
	m_refGlademmXml->get_widget("menuitem_viewtoolbar", pMenuItemViewToolbar);
	if(pMenuItemViewToolbar){ 
		pMenuItemViewToolbar->signal_toggled().connect( sigc::mem_fun( *this, &GlkmMainWindow::on_menuitem_viewtoolbar_toggled) );
	}
	//Connect signal handlers for the main window "menu help" items:
	pMenuItemAbout = NULL;
	m_refGlademmXml->get_widget("menuitem_about", pMenuItemAbout);
	if(pMenuItemAbout){
		pMenuItemAbout->signal_activate().connect( sigc::mem_fun( *this, &GlkmMainWindow::on_menuitem_about_activated) ); 
	}
	
}


GlkmMainWindow::~GlkmMainWindow()
{
	//Null
}


void GlkmMainWindow::on_button_clicked()
{
	//TODO
}


void GlkmMainWindow::on_menuitem_quit_activated()
{
	std::cout << "menu quit activated" << std::endl;
	hide();
}

void GlkmMainWindow::on_menuitem_viewtoolbar_toggled()
{
	std::cout << "menu viewtoolbar toggled" << std::endl;
}

void GlkmMainWindow::on_menuitem_about_activated()
{
	std::cout << "menu about activated" << std::endl;
	pGlkmAboutDialog->show();
	  //Bring it to the front, in case it was already shown:
	pGlkmAboutDialog->present();

}

