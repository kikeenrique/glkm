/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * glkm_aboutdialog.cc
 * Copyright (C) Enrique García Álvarez 2007 <kike @ eldemonionegro.com>
 * 
 * glkm_aboutdialog.cc is free software.
 * 
 * You may redistribute it and/or modify it under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 * 
 * main.cc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with main.cc.  If not, write to:
 * 	The Free Software Foundation, Inc.,
 * 	51 Franklin Street, Fifth Floor
 * 	Boston, MA  02110-1301, USA.
 */

#include "glkm_mainwindow.h"
//#include <libglademm/xml.h>
#include <iostream>
//#include <gtkmm.h>


GlkmMainWindow::GlkmMainWindow()
{
	//Load the Glade file and instiate its widgets:
	try
	{
		m_refGlademmXml = Gnome::Glade::Xml::create(GLADE_FILE);
	}
	catch(const Gnome::Glade::XmlError& ex)
    {
		std::cerr << ex.what() << std::endl;
//LANZAR ERROR
//		return 1; 
	}	
//	m_refGlademmXml->get_widget("vbox1");
	m_refGlademmXml->reparent_widget("vbox1", *this);

	m_refGlademmXml->get_widget_derived("glkm_aboutdialog", Glkm_AboutDialog);

	//Connect signal handlers for the menu items:
		pMenuQuit = 0;
		m_refGlademmXml->get_widget("menu_quit", pMenuQuit);
		if(pMenuQuit){
			pMenuQuit->signal_activate().connect( sigc::mem_fun( *this, &GlkmMainWindow::on_menu_quit_activated) ); 
		}

		pMenuAbout = 0;
		m_refGlademmXml->get_widget("menu_about", pMenuAbout);
		if(pMenuAbout){
			pMenuAbout->signal_activate().connect( sigc::mem_fun( *this, &GlkmMainWindow::on_menu_about_activated) ); 
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


void GlkmMainWindow::on_menu_quit_activated()
{
	std::cout << "menu quit activated" << std::endl;
	hide();
}


void GlkmMainWindow::on_menu_about_activated()
{
	std::cout << "menu about activated" << std::endl;
	Glkm_AboutDialog->show();
}

