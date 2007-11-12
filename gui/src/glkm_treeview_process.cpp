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

#include "glkm_treeview_process.hpp"
#include <iostream>

#ifdef HAVE_LIBGNOME
#include <libgnome/gnome-url.h>
#endif // HAVE_LIBGNOME

#ifdef DEBUG
#include "debug.hpp"
#endif // DEBUG


TreeViewProcess::TreeViewProcess(BaseObjectType* cobject, const Glib::RefPtr<Gnome::Glade::Xml>& refGlade)
	:Gtk::TreeView(cobject),
	m_refGlademmXml(refGlade)
{

	//Create the Tree model
	m_refTreeModel = Gtk::TreeStore::create(m_Columns);
	set_model(m_refTreeModel);
	//All the items to be reordered with drag-and-drop
	set_reorderable();

	//Allow multiple selection
	m_refTreeSelection = get_selection();
//	m_refTreeSelection->set_mode(Gtk::SELECTION_MULTIPLE);
	m_refTreeSelection->set_mode(Gtk::SELECTION_SINGLE);

	m_refTreeSelection->selected_foreach_iter(sigc::mem_fun(*this,
																						        &TreeViewProcess::on_selected_row_callback) );

	//Connect signal handlers for the treeview "menu popup treeview process" :
	pm_Menu_Popup_TreeView_Process = NULL;
	m_refGlademmXml->get_widget("menu_popup_treeview_process", pm_Menu_Popup_TreeView_Process);
	if (pm_Menu_Popup_TreeView_Process){
//TODO		pm_Menu_Popup_TreeView_Process->signal_activate().connect( sigc::mem_fun( *this, &GlkmMainWindow::on_menuitem_quit_activated) );
	}

	pm_Menuitem_Update = NULL;
	m_refGlademmXml->get_widget("menuitem_update", pm_Menuitem_Update);
	if (pm_Menuitem_Update){
		pm_Menuitem_Update->signal_activate().connect( sigc::mem_fun( *this, &TreeViewProcess::on_menu_file_popup_generic) );
	}

	//Fill the TreeView's model
	Gtk::TreeModel::Row row = *(m_refTreeModel->append());
	row[m_Columns.m_col_id] = 1;
  	row[m_Columns.m_col_name] = "Billy Bob";

	Gtk::TreeModel::Row childrow = *(m_refTreeModel->append(row.children()));
	childrow[m_Columns.m_col_id] = 11;
	childrow[m_Columns.m_col_name] = "Billy Bob Junior";

	childrow = *(m_refTreeModel->append(row.children()));
	childrow[m_Columns.m_col_id] = 12;
	childrow[m_Columns.m_col_name] = "Sue Bob";

	row = *(m_refTreeModel->append());
	row[m_Columns.m_col_id] = 2;
	row[m_Columns.m_col_name] = "Joey Jojo";

	row = *(m_refTreeModel->append());
	row[m_Columns.m_col_id] = 3;
	row[m_Columns.m_col_name] = "Rob McRoberts";

	childrow = *(m_refTreeModel->append(row.children()));
	childrow[m_Columns.m_col_id] = 31;
	childrow[m_Columns.m_col_name] = "Xavier McRoberts";

	
	//Add the TreeView's view columns:
//	append_column_editable("PID", m_Columns.m_col_id);
	append_column("PID", m_Columns.m_col_id);
	append_column("PName", m_Columns.m_col_name);
	
	//Connect signal:
	signal_row_activated().connect(sigc::mem_fun(*this,
																		    &TreeViewProcess::on_treeview_row_activated) );

	//Expand all children
	expand_all();
	show_all_children();
}

TreeViewProcess::~TreeViewProcess()
{
	//Null
}

void TreeViewProcess::on_treeview_row_activated (const Gtk::TreeModel::Path& path,	    /* */
																				Gtk::TreeViewColumn*	 						/* Column */ )
{
	Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter(path);
	if (iter) {
		Gtk::TreeModel::Row row = *iter;
		std::cout << "Row activated: ID=" << row[m_Columns.m_col_id] 
					<< ", Name=" << row[m_Columns.m_col_name]
					<< std::endl;
	}
}

void TreeViewProcess::on_selected_row_callback(const Gtk::TreeModel::iterator& iter)
{
	Gtk::TreeModel::Row row = *iter;
	//Do something with the row.
	//TODO
}

bool TreeViewProcess::on_button_press_event(GdkEventButton* event)
{
	//Call base class, to allow normal handling,
	//such as allowing the row to be selected by the right-click:
	bool return_value = TreeView::on_button_press_event(event);
	//Then do our custom stuff:
	if ( (event->type == GDK_BUTTON_PRESS) && (event->button == 3) )
	{
		pm_Menu_Popup_TreeView_Process->popup(event->button, event->time);
	}
	return return_value;
}

void TreeViewProcess::on_menu_file_popup_generic()
{
	std::cout << "A popup menu item was selected." << std::endl;
	m_refTreeSelection = get_selection();
	if (m_refTreeSelection)
	{
		Gtk::TreeModel::iterator iter = m_refTreeSelection->get_selected();
		if (iter)
		{
			int id = (*iter)[m_Columns.m_col_id];
			std::cout << "Selected ID=" << id << std::endl;
		}
	}
}
