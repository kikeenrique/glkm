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

#ifndef _TREEVIEWHOST_HPP
#define _TREEVIEWHOST_HPP

#include <gtkmm/treeview.h>
//#include <gtkmm/treestore.h>
#include <gtkmm/treemodel.h>

#include "utils.hpp"

class TreeViewHost : public Gtk::TreeView {

  public:
	TreeViewHost(BaseObjectType* cobject, const RefPtrGladeXml & refGlade);
	virtual ~TreeViewHost();

  protected:
	RefPtrGladeXml _refPtrGlademmXml;
	
	//Signal handlers:
	virtual void on_treeview_row_activated(const Gtk::TreeModel::Path & path, 
			  		       Gtk::TreeViewColumn * column);
	void on_selected_row_callback(const Gtk::TreeModel::iterator & iter);
	// Override Signal handler:
	// Alternatively, use signal_button_press_event().connect_notify()
	virtual bool on_button_press_event(GdkEventButton *ev);

	//Signal handler for popup menu items:
	virtual void on_menu_file_popup_generic();

	//
	void fill_model();


	//Tree model columns:
	class ModelColumns : public Gtk::TreeModel::ColumnRecord {
	public:
		ModelColumns() {
			add(col_id);
			add(col_name);
		}
		TreeModelColumnInt col_id;
		TreeModelColumnUstring col_name;
	};

	ModelColumns			_ModelColumns;
	RefPtrTreeStore			_refPtrTreeStore;
	RefPtrTreeSelection		_refPtrTreeSelection;

	Gtk::Menu*				_pMenu_Popup_TreeView_Host;
	Gtk::MenuItem*				_pMenuitem_Refresh;
	
};

#endif //_TREEVIEWHOST_HPP
