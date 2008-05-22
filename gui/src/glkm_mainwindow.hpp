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

#ifndef _MAINWINDOW_HPP
#define _MAINWINDOW_HPP

#include <gtkmm/window.h>
//#include <gtkmm/imagemenuitem.h>
#include "utils.hpp"

class TreeViewHost;
class StatusBar;
class AboutDialog;
namespace Gtk{
	class ImageMenuItem;
	class CheckMenuItem;
	class ToolButton;
	class Toolbar;	
}

#include <config.h>

class MainWindow : public Gtk::Window
{
public:
	MainWindow();
	virtual ~MainWindow();

protected:
	RefPtrGladeXml _refGlademmXml;
// Future mapping #include <libglademm/variablesmap.h>
//	Gnome::Glade::VariablesMap* m_pVariablesMap;
	unsigned int			_ContextId;

	/*   *** Signal handlers ***
			Menu File
	*/
	void on_menuitem_quit_activated();

	/* 
			Menu Edit
	*/

	/* 
			Menu View
	*/
	void on_menuitem_viewtoolbar_toggled();
	
	/* 
			Menu Help
	*/
	void on_menuitem_about_activated();

	/* 
			Toolbar
	*/

	void on_clicked_toolbar_connect();
	void on_clicked_toolbar_refresh();
		
	/*   *** Child widgets ***
			Menu File
	*/
	Gtk::ImageMenuItem * _pMenuItemQuit;
	
	/* 
			Menu Edit
	*/
	Gtk::ImageMenuItem * _pMenuItemCopy;
	Gtk::ImageMenuItem * _pMenuItemCut;
	Gtk::ImageMenuItem * _pMenuItemDelete;

	/* 
			Menu View
	*/
	Gtk::CheckMenuItem * _pMenuItemViewToolbar;
	
	/* 
			Menu Help
	*/
	Gtk::ImageMenuItem * _pMenuItemAbout;


	/*		Main Window UI
	*/
	TreeViewHost *			_pTreeViewHost;
	StatusBar *			_pStatusBar;
	Gtk::ToolButton * 		_pToolButton_Connect;
	Gtk::Toolbar *			_pToolbar;
	Gtk::ToolButton *		_pToolButton_Refresh;	
	
	/*
			SubWindows
	*/
	AboutDialog *		_pAboutDialog;
		
};

#endif //_MAINWINDOW_HPP
