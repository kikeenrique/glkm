/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * glkm_mainwindow.h
 * Copyright (C) Enrique García Álvarez 2007 <kike @ eldemonionegro.com>
 * 
 * glkm_mainwindow.h is free software.
 * 
 * You may redistribute it and/or modify it under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 * 
 * glkm_mainwindow.h is distributed in the hope that it will be useful,
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

#ifndef GLKM_MAINWINDOW_H
#define GLKM_MAINWINDOW_H

#include <config.h>
#include <gtkmm.h>
#include <libglademm/xml.h>
// Future mapping #include <libglademm/variablesmap.h>
#include "glkm_aboutdialog.h"

/* For testing propose use the local (not installed) glade file */
//#define GLADE_FILE  PACKAGE_DATA_DIR "/glkm/glade/glkm.glade" 
#define GLADE_FILE  "/home/enrgar/svn/pfc/trunk/gui/data/glkm.glade" 

class GlkmMainWindow : public Gtk::Window
{
public:
	GlkmMainWindow();
	virtual ~GlkmMainWindow();

protected:
	Glib::RefPtr<Gnome::Glade::Xml> m_refGlademmXml;	
//	Gnome::Glade::VariablesMap* m_pVariablesMap;

	/* Signal handlers:
			Menu
	*/
	virtual void on_button_clicked();
	virtual void on_menu_quit_activated();
	virtual void on_menu_about_activated();

	/* Child widgets:
			Menu
	*/
	Gtk::MenuItem* pMenuItem;
	
	Gtk::MenuItem* pMenuQuit;

	Gtk::MenuItem* pMenuAbout;
	
	/* Child widgets:
			SubWindows
	*/
	GlkmAboutDialog* pGlkmAboutDialog;
};

#endif //GLKM_MAINWINDOW_H
