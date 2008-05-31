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

#include "tree-view-host.hpp"

#include "config.h"
#include "debug.hpp"

 
TreeViewHost::TreeViewHost(BaseObjectType* cobject, const RefPtrGladeXml& refGlade):
	Gtk::TreeView(cobject),
	_refPtrGlademmXml(refGlade)
{
	//Create the Tree model
	_refPtrTreeStore = Gtk::TreeStore::create(_ModelColumns);
	set_model(_refPtrTreeStore);
	//All the items to be reordered with drag-and-drop
	set_reorderable();

	//Allow multiple selection
	_refPtrTreeSelection = get_selection();
//	_refPtrTreeSelection->set_mode(Gtk::SELECTION_MULTIPLE);
	_refPtrTreeSelection->set_mode(Gtk::SELECTION_SINGLE);

	_refPtrTreeSelection->selected_foreach_iter(sigc::mem_fun(*this,
														   &TreeViewHost::on_selected_row_callback) );

	//Connect signal handlers for the treeview "menu popup treeview host" :
	_pMenu_Popup_TreeView_Host = NULL;
	_refPtrGlademmXml->get_widget("menu_popup_treeview_host", _pMenu_Popup_TreeView_Host);
	if (_pMenu_Popup_TreeView_Host){
//TODO		pm_Menu_Popup_TreeView_Host->signal_activate().connect( sigc::mem_fun( *this, &GlkmMainWindow::on_menuitem_quit_activated) );
	}
	_pMenuitem_Refresh = NULL;
	_refPtrGlademmXml->get_widget("menuitem_refresh", _pMenuitem_Refresh);
	if (_pMenuitem_Refresh) {
		_pMenuitem_Refresh->signal_activate().connect(sigc::mem_fun(*this,
																	&TreeViewHost::on_menu_file_popup_generic) );
	}

	//Fill the TreeView's model
	fill_model();
	
	//Add the TreeView's view columns:
//	append_column_editable("PID", _modelColumns.col_id);
	append_column("PID", _ModelColumns.col_id);
	append_column("Name", _ModelColumns.col_name);
	
	//Connect signal:
	signal_row_activated().connect(sigc::mem_fun(
								*this,
							    &TreeViewHost::on_treeview_row_activated) );

	//Expand all children
	expand_all();
	show_all_children();
}

TreeViewHost::~TreeViewHost(){
	//Null
}

/*
void TreeViewHost::add_process_to_model(const Procces & p){
	Gtk::TreeStore::Row row = *(_refPtrTreeStore->append());
	row[_modelColumns.col_id] = p.get_PID();
 	row[_modelColumns.col_name] = p.get_name();
}
*/

void TreeViewHost::fill_model(){
	Gtk::TreeStore::Row row = *(_refPtrTreeStore->append());
	row[_ModelColumns.col_id] = 1;
  	row[_ModelColumns.col_name] = "Billy Bob";

	Gtk::TreeStore::Row childrow = *(_refPtrTreeStore->append(row.children()));
	childrow[_ModelColumns.col_id] = 11;
	childrow[_ModelColumns.col_name] = "Billy Bob Junior";

	childrow = *(_refPtrTreeStore->append(row.children()));
	childrow[_ModelColumns.col_id] = 12;
	childrow[_ModelColumns.col_name] = "Sue Bob";

	row = *(_refPtrTreeStore->append());
	row[_ModelColumns.col_id] = 2;
	row[_ModelColumns.col_name] = "Joey Jojo";

	row = *(_refPtrTreeStore->append());
	row[_ModelColumns.col_id] = 3;
	row[_ModelColumns.col_name] = "Rob McRoberts";

	childrow = *(_refPtrTreeStore->append(row.children()));
	childrow[_ModelColumns.col_id] = 31;
	childrow[_ModelColumns.col_name] = "Xavier McRoberts";
}

/*
 *
 */
void TreeViewHost::on_treeview_row_activated (const Gtk::TreeModel::Path& path,
											  Gtk::TreeViewColumn*){
	Gtk::TreeModel::iterator iter = _refPtrTreeStore->get_iter(path);
	if (iter) {
		Gtk::TreeModel::Row row = *iter;
		PRINTD("Row activated: ID=" + row[_ModelColumns.col_id] 
			   + std::string(", Name=") + row[_ModelColumns.col_name] );
	}
}

void TreeViewHost::on_selected_row_callback(const Gtk::TreeModel::iterator& iter){
	Gtk::TreeModel::Row row = *iter;
	//Do something with the row.
	//TODO
}

bool TreeViewHost::on_button_press_event(GdkEventButton* event){
	//Call base class, to allow normal handling,
	//such as allowing the row to be selected by the right-click:
	bool return_value = TreeView::on_button_press_event(event);
	//Then do our custom stuff:
	if ( (event->type == GDK_BUTTON_PRESS) && (event->button == 3) )
	{
		_pMenu_Popup_TreeView_Host->popup(event->button, event->time);
	}
	return return_value;
}

void TreeViewHost::on_menu_file_popup_generic(){
	PRINTD("A popup menu item was selected.");
	_refPtrTreeSelection = get_selection();
	if (_refPtrTreeSelection)
	{
		Gtk::TreeModel::iterator iter = _refPtrTreeSelection->get_selected();
		if (iter)
		{
			int id = (*iter)[_ModelColumns.col_id];
			PRINTD("Selected ID=" + id );
		}
	}
}
