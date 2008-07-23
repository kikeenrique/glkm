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

#ifndef _TREE_VIEW_HOST_HPP
#define _TREE_VIEW_HOST_HPP

#include <gtkmm/treeview.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treeviewcolumn.h>
#include <gtkmm/menu.h>
#include <gtkmm/menuitem.h>

#include "utils.hpp"

class Host;
class Process;

class TreeViewHost : public Gtk::TreeView {

  public:
	TreeViewHost(BaseObjectType* cobject, const RefPtrGladeXml & refGlade);
	virtual ~TreeViewHost();

	Host * take_Host();
	void set__pHost(Host * value);

	void on_process_added(const Process & process);
	void on_process_removed(const Process & process);

  protected:
	RefPtrGladeXml _refPtrGlademmXml;

	bool find_parent_process(const Process & process,
				  Gtk::TreeModel::iterator & found_iter);
	bool find_process(const Process & process,
			  Gtk::TreeModel::iterator & found_iter);
	bool find_process_by_PID_from_here(int PID,
					   const Gtk::TreeModel::iterator & from_iter,
					   Gtk::TreeModel::iterator & found_iter);

	//Signal handlers:
	void on_treeview_row_activated(const Gtk::TreeModel::Path & path, 
			  		       Gtk::TreeViewColumn * column);
	void on_selected_row_callback(const Gtk::TreeModel::iterator & iter);

	// Override Signal handler:
	// Alternatively, use signal_button_press_event().connect_notify()
	virtual bool on_button_press_event(GdkEventButton *ev);

	//Signal handler for popup menu items:
	void on_menu_popup_refresh();

	//Tree model columns:
	class ModelColumns : public Gtk::TreeModel::ColumnRecord {
	public:
		ModelColumns() {
			add(col_PID);
			add(col_name);
			add(col_PPID);
		}
		TreeModelColumnInt col_PID;
		TreeModelColumnUstring col_name;
		TreeModelColumnInt col_PPID;
	};

	ModelColumns			_ModelColumns;
	RefPtrTreeStore			_refPtrTreeStore;
	RefPtrTreeSelection		_refPtrTreeSelection;

	Gtk::Menu*			_pMenu_Popup_TreeView_Host;
	Gtk::MenuItem*			_pMenuitem_Refresh;

	Host * _pHost;
};

#endif //_TREE_VIEW_HOST_HPP
