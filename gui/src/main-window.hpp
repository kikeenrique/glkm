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

class StatusBar;
class AboutDialog;
class HostSelectDialog;
class NotebookHosts;
class Controller;

class MainWindow : public Gtk::Window
{
public:
	MainWindow();
	virtual ~MainWindow();

	HostSelectDialog * _pHostSelectDialog;

protected:
	RefPtrGladeXml _refPtrGlademmXml;

	unsigned int		_ContextId;

	//	      Menu File
	void on_imagemenuitem_quit_activated();

	Gtk::ImageMenuItem * _pImageMenuItemQuit;

	//		Menu Edit
	void on_imagemenuitem_cut_activated();
	void on_imagemenuitem_copy_activated();
	void on_imagemenuitem_paste_activated();
	void on_imagemenuitem_delete_activated();

	Gtk::ImageMenuItem * _pImageMenuItemCopy;
	Gtk::ImageMenuItem * _pImageMenuItemCut;
	Gtk::ImageMenuItem * _pImageMenuItemPaste;
	Gtk::ImageMenuItem * _pImageMenuItemDelete;

	//	      Menu View
	void on_checkmenuitem_viewtoolbar_toggled();
	void on_checkmenuitem_viewdebug_toggled();

	Gtk::CheckMenuItem * _pCheckMenuItemViewToolbar;
	Gtk::CheckMenuItem * _pCheckMenuItemViewDebug;

	//		Menu Help
	void on_imagemenuitem_about_activated();

	Gtk::ImageMenuItem * _pImageMenuItemAbout;

	//		Toolbar
	void on_clicked_toolbar_select();
	void on_clicked_toolbar_connect();
	void on_clicked_toolbar_synchronize();
		
	Gtk::Toolbar *		_pToolbar;
	Gtk::ToolButton * 	_pToolButton_Select;
	Gtk::ToolButton *	_pToolButton_Connect;
	Gtk::ToolButton *	_pToolButton_Synchronize;

	//		Main Window (Important stuff)
	NotebookHosts *		_pNotebookHosts;
	StatusBar *		_pStatusBar;
	
	//		SubWindows
	AboutDialog *		_pAboutDialog;
	Gtk::Window *		_pWindowDebug;
};

#endif //_MAIN_WINDOW_HPP
