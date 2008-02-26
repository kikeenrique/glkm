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

#ifndef GLKM_MAINWINDOW_HPP
#define GLKM_MAINWINDOW_HPP

#include <config.h>
#include <gtkmm.h>
#include <libglademm/xml.h>
// Future mapping #include <libglademm/variablesmap.h>
#include "glkm_aboutdialog.hpp"
#include "glkm_treeview_process.hpp"
#include "glkm_statusbar.hpp"


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


	/*   *** Signal handlers ***
			Menu File
	*/
	virtual void on_menuitem_quit_activated();

	/* 
			Menu Edit
	*/

	/* 
			Menu View
	*/
	virtual void on_menuitem_viewtoolbar_toggled();
	
	/* 
			Menu Help
	*/
	virtual void on_menuitem_about_activated();

	/* 
			Toolbar
	*/

	void on_clicked_toolbar_connect();
		
	/*   *** Child widgets ***
			Menu File
	*/
	Gtk::ImageMenuItem* pMenuItemQuit;
	
	/* 
			Menu Edit
	*/
	Gtk::ImageMenuItem* pMenuItemCopy;
	Gtk::ImageMenuItem* pMenuItemCut;
	Gtk::ImageMenuItem* pMenuItemDelete;

	/* 
			Menu View
	*/
	Gtk::CheckMenuItem* pMenuItemViewToolbar;
	
	/* 
			Menu Help
	*/
	Gtk::ImageMenuItem* pMenuItemAbout;


	/*		Main Window UI
	*/
	TreeViewProcess*		pGlkmTreeViewProcess;
	GlkmStatusBar*			pGlkmStatusBar;
	unsigned int			m_ContextId;
	Gtk::ToolButton* 		mp_button_connect;
	Gtk::Toolbar*			mp_toolbar_mainwindow;
	
	/*
			SubWindows
	*/
	GlkmAboutDialog* pGlkmAboutDialog;
	
private:
		
};

#endif //GLKM_MAINWINDOW_HPP
