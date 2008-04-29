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

#ifndef GLKM_TREEVIEWHOST_HPP
#define GLKM_TREEVIEWHOST_HPP

#include <config.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treestore.h>
#include <libglademm/xml.h>


class TreeViewHost : public Gtk::TreeView
{
public:
	TreeViewHost(BaseObjectType* cobject, 
		     const Glib::RefPtr<Gnome::Glade::Xml>& refGlade);
	virtual ~TreeViewHost();

protected:
	//Signal handlers:
	virtual void on_treeview_row_activated(const Gtk::TreeModel::Path& path, 
			  		       Gtk::TreeViewColumn* column);
	void on_selected_row_callback(const Gtk::TreeModel::iterator& iter);
	// Override Signal handler:
	// Alternatively, use signal_button_press_event().connect_notify()
	virtual bool on_button_press_event(GdkEventButton *ev);

	//Signal handler for popup menu items:
	virtual void on_menu_file_popup_generic();

	//
	void myfill();
	
	Glib::RefPtr<Gnome::Glade::Xml> m_refGlademmXml;
	
	//Tree model columns:
	class ModelColumns : public Gtk::TreeModel::ColumnRecord
	{
	public:
		ModelColumns()
		{
			add(m_col_id);
			add(m_col_name);
		}
			Gtk::TreeModelColumn<int> m_col_id;
			Gtk::TreeModelColumn<Glib::ustring> m_col_name;
	};

	ModelColumns				m_Columns;
	Glib::RefPtr<Gtk::TreeStore>		m_refTreeModel;
	Glib::RefPtr<Gtk::TreeSelection>	m_refTreeSelection;

	Gtk::Menu*				pm_Menu_Popup_TreeView_Host;
	Gtk::MenuItem*				pm_Menuitem_Update;
	
};

#endif //GLKM_TREEVIEWHOST_HPP
