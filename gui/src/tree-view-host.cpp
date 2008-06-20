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
#include "host.hpp"
#include "process.hpp"

#include "config.h"
#include "debug.hpp"

//TODO temporal
#define GLADE_FILE  "/home/enrgar/svn/pfc/trunk/gui/data/glkm.glade" 

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
//TODO this must be fixed sometime, this is not a proper way to do this	
	RefPtrGladeXml _refPtrGlademmXml2;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
	try {
		_refPtrGlademmXml2 = Gnome::Glade::Xml::create(GLADE_FILE, "notebook_hosts-treeview_host-menu");
	}
	catch(const Gnome::Glade::XmlError& exception) {
		std::cerr << exception.what() << std::endl;
		throw; 
	}	
#else
	std::auto_ptr<Gnome::Glade::XmlError> error;
	_refPtrGlademmXml2 = Gnome::Glade::Xml::create(GLADE_FILE, "notebook_hosts-treeview_host-menu", "", error);
	if (error.get()){
		std::cerr << error->what() << std::endl;
		return 1;
	}
#endif //GLIBMM_EXCEPTIONS_ENABLED
	_pMenu_Popup_TreeView_Host = NULL;
	_refPtrGlademmXml2->get_widget("notebook_hosts-treeview_host-menu", _pMenu_Popup_TreeView_Host);
	if (_pMenu_Popup_TreeView_Host){
	}
	_pMenuitem_Refresh = NULL;
	_refPtrGlademmXml2->get_widget("notebook_hosts-treeview_host-menu-menuitem-refresh", _pMenuitem_Refresh);
	if (_pMenuitem_Refresh) {
		_pMenuitem_Refresh->signal_activate().connect(sigc::mem_fun(*this,
																	&TreeViewHost::on_menu_popup_refresh) );
	}

	//Fill the TreeView's model
//	fill_model();
	
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


Host * TreeViewHost::take_Host() {
	return _pHost;
}

void TreeViewHost::set__pHost(Host * value) {
  _pHost = value;
}

void TreeViewHost::on_Process_added(const Process & process) {
	int PID = process.get__PID();
	int PPID = process.get__PPID();
	PRINTD("TreeViewHost::on_Process_added " + process.get__name());
	PRINTD(PPID);

	if (PPID == 0) {
		// When parent process is kernel
		Gtk::TreeStore::Row row = *(_refPtrTreeStore->append());
		row[_ModelColumns.col_id] = PID;
	  	row[_ModelColumns.col_name] = "kernel " + process.get__name();
	} else if (PPID == 1) {
		// When parent process is init
		Gtk::TreeStore::Row row = *(_refPtrTreeStore->append());
		row[_ModelColumns.col_id] = PID;
	  	row[_ModelColumns.col_name] = process.get__name();
	} else {
		// When parent process is other process look for it and let assume its
		// responsability...
		Gtk::TreeStore::Children children = _refPtrTreeStore->children();
		Gtk::TreeStore::iterator iter;
		for(iter = children.begin(); iter != children.end(); ++iter) {
			Gtk::TreeModel::Row row = *iter;
			// When parent process is founded, appendit as children and exit
			if (row[_ModelColumns.col_id] == PPID ) {
				Gtk::TreeStore::Row childrow = *(_refPtrTreeStore->append(row.children()));
				childrow[_ModelColumns.col_id] = PID;
				childrow[_ModelColumns.col_name] = process.get__name();
				break;
			}
		}
	}
}

/*
 *
 */
void TreeViewHost::on_treeview_row_activated (const Gtk::TreeModel::Path& path,
											  Gtk::TreeViewColumn*){
	Gtk::TreeModel::iterator iter = _refPtrTreeStore->get_iter(path);
	if (iter) {
		Gtk::TreeModel::Row row = *iter;
		int PID = (*iter)[_ModelColumns.col_id];
		PRINTD("TreeViewHost::Row activated: ID=");
		PRINTD(PID);
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

void TreeViewHost::on_menu_popup_refresh(){
	_refPtrTreeSelection = get_selection();
	if (_refPtrTreeSelection)
	{
		Gtk::TreeModel::iterator iter = _refPtrTreeSelection->get_selected();
		if (iter)
		{
			int PID = (*iter)[_ModelColumns.col_id];
			PRINTD("TreeViewHost::Row activated: ID=");
			PRINTD(PID);
		}
	}
}
