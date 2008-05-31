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

#ifndef _MAIN_WINDOW_HPP
#define _MAIN_WINDOW_HPP

#include <gtkmm/window.h>
#include <gtkmm/imagemenuitem.h>
#include <gtkmm/checkmenuitem.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/toolbar.h>
#include "utils.hpp"

class Hosts;
class TreeViewHost;
class StatusBar;
class AboutDialog;
class HostSelectDialog;

class MainWindow : public Gtk::Window
{
public:
	MainWindow();
	virtual ~MainWindow();

	HostSelectDialog *      _pHostSelectDialog;

protected:
	RefPtrGladeXml _refGlademmXml;

	//Provides access to Controller-Model
	Hosts * _pHosts;

	unsigned int			_ContextId;

	/*   *** Signal handlers ***
			Menu File
	*/
	void on_imagemenuitem_quit_activated();

	/* 
			Menu Edit
	*/
	void on_imagemenuitem_cut_activated();
	void on_imagemenuitem_copy_activated();
	void on_imagemenuitem_paste_activated();
	void on_imagemenuitem_delete_activated();

	/* 
			Menu View
	*/
	void on_checkmenuitem_viewtoolbar_toggled();
	
	/* 
			Menu Help
	*/
	void on_imagemenuitem_about_activated();

	/* 
			Toolbar
	*/

	void on_clicked_toolbar_select();
	void on_clicked_toolbar_connect();
	void on_clicked_toolbar_refresh();
		
	/*   *** Child widgets ***
			Menu File
	*/
	Gtk::ImageMenuItem * _pImageMenuItemQuit;
	
	/* 
			Menu Edit
	*/
	Gtk::ImageMenuItem * _pImageMenuItemCopy;
	Gtk::ImageMenuItem * _pImageMenuItemCut;
	Gtk::ImageMenuItem * _pImageMenuItemPaste;
	Gtk::ImageMenuItem * _pImageMenuItemDelete;

	/* 
			Menu View
	*/
	Gtk::CheckMenuItem * _pCheckMenuItemViewToolbar;
	
	/* 
			Menu Help
	*/
	Gtk::ImageMenuItem * _pImageMenuItemAbout;


	/*		Main Window UI
	*/
	TreeViewHost *			_pTreeViewHost;
	StatusBar *			_pStatusBar;
	Gtk::Toolbar *			_pToolbar;
	Gtk::ToolButton * 		_pToolButton_Select;
	Gtk::ToolButton *		_pToolButton_Connect;
	Gtk::ToolButton *		_pToolButton_Refresh;
	
	/*
			SubWindows
	*/
	AboutDialog *		_pAboutDialog;

};

#endif //_MAIN_WINDOW_HPP
