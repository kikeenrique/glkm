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
//	append_column_editable("PID", _modelColumns.col_PID);
	append_column("PID", _ModelColumns.col_PID);
	append_column("Name", _ModelColumns.col_name);
	
	//Connect signal:
	signal_row_activated().connect(sigc::mem_fun(
								*this,
							    &TreeViewHost::on_treeview_row_activated) );

//	foreach_Proccess_added = sigc::mem_fun(*this, &TreeViewHost::on_foreach_Proccess_added);


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

/*
 *
 */
void TreeViewHost::on_process_added(const Process & process) {
	PRINTD("TreeViewHost::on_process_added " + process.get__name());
	Gtk::TreeStore::iterator process_iter;

	int PPID = process.get__PPID();
	int PID = process.get__PID();

	if ( find_parent_process (process, process_iter) ) {
		Gtk::TreeStore::Row row = *process_iter;
		Gtk::TreeStore::Row childrow = *(_refPtrTreeStore->append(row.children()));
		childrow[_ModelColumns.col_PID] = PID;
		childrow[_ModelColumns.col_PPID] = PPID;
		childrow[_ModelColumns.col_name] = process.get__name();
		PRINTD("TreeViewHost::on_process_added process has been added " + process.get__name());
	} else {
		PRINTD("WARNING TreeViewHost::on_process_added process not found, parent not found " + process.get__name());
	}

}
/*	int PPID = process.get__PPID();
	int PID = process.get__PID();
	std::cout << "Parent is PPID:" << PPID << " PID:" << PID << " n:" << process.get__name() << std::endl;
	if ( find_proccess_by_PID_from_here (PPID, root_iter, result_iter) ) {
		Gtk::TreeModel::Row row = *result_iter;
		Gtk::TreeStore::Row childrow = *(_refPtrTreeStore->append(row.children()));
		childrow[_ModelColumns.col_PID] = PID;
		childrow[_ModelColumns.col_PPID] = PPID;
		childrow[_ModelColumns.col_name] = process.get__name();
		std::cout << "TreeViewHost::on_process_added process has been added" << std::endl;
	} else {
		std::cout << "WARNING TreeViewHost::on_process_added process not found, parent not found" << std::endl;
	}*/

/*	PRINTD("TreeViewHost::on_process_added " + process.get__name());

	Gtk::TreeStore::iterator root_iter = _refPtrTreeStore->get_iter("0");
	Gtk::TreeStore::iterator result_iter;
	Gtk::TreeModel::Row row;
	int PPID = process.get__PPID();
	int PID = process.get__PID();
	
	if (PPID == 0) {
		// When parent process is kernel
		std::cout << "Parent is KERNEL PPID:" << PPID << " PID:" << PID << " n:" << process.get__name() << std::endl;
		row = *(_refPtrTreeStore->append());
		row[_ModelColumns.col_PID] = PID;
		row[_ModelColumns.col_PPID] = PPID;
	  	row[_ModelColumns.col_name] = "[K]" + process.get__name();
	} else {
			// Search for parent process.
		if ( find_proccess_by_PID_from_here (PPID, root_iter, result_iter) ) {
			std::cout << "Parent is PPID:" << PPID << " PID:" << PID << " n:" << process.get__name() << std::endl;
			// When parent found and process exists     -> do nothing
			//        "              process NOT exists -> add it

			row = *result_iter;
			//If process PID exists in TreeModel then we do nothing
			Gtk::TreeStore::Children children = row.children();
			Gtk::TreeStore::iterator children_iter;
			bool found = false;
			for(children_iter = children.begin(); children_iter != children.end(); ++children_iter) {
				row = *children_iter;
				if (row[_ModelColumns.col_PID] == PID ) {
					std::cout << "Process exists" << std::endl;
					found=true;
				}
			}
			if (!found) {
				std::cout << "Adding PID:" << PID << " n:" << process.get__name() << std::endl;
				row = *result_iter;
				Gtk::TreeStore::Row childrow = *(_refPtrTreeStore->append(row.children()));
				childrow[_ModelColumns.col_PID] = PID;
				childrow[_ModelColumns.col_PPID] = PPID;
				childrow[_ModelColumns.col_name] = process.get__name();
			}
		} 
	}
	std::cout << "start added_looking by PID:" << PID << " PPID:" << PPID << std::endl;
}

*/
/*	
	int PID = process.get__PID();
	int PPID = process.get__PPID();
	PRINTD("TreeViewHost::on_process_added " + process.get__name());	

	Gtk::TreeStore::Row row;
	if (PPID == 0) {
		// When parent process is kernel
		row = *(_refPtrTreeStore->append());
		row[_ModelColumns.col_PID] = PID;
		row[_ModelColumns.col_PPID] = PPID;
	  	row[_ModelColumns.col_name] = "[K]" + process.get__name();
	} else {
		// When parent process is other process look for it and let assume its
		// responsability...
		Gtk::TreeStore::Children children = _refPtrTreeStore->children();
		Gtk::TreeStore::iterator children_iter;
		bool found = false;
		for(children_iter = children.begin(); children_iter != children.end(); ++children_iter) {
			if (add_proccess_to_parent(children_iter, process)) {
				found = true;
				break;
			}
		}
	}
*/
//////////////////////////////////////////////
//		_refPtrTreeStore->foreach_iter(foreach_Proccess_added);

/*		Gtk::TreeStore::Children children = _refPtrTreeStore->children();
		Gtk::TreeStore::iterator iter;
		for(iter = children.begin(); iter != children.end(); ++iter) {
//		Gtk::TreeStore::reverse_iterator iter;
//		for(iter = children.rbegin(); iter != children.rend(); ++iter) {
			Gtk::TreeModel::Row row_it = *iter;
			PRINTD("TreeViewHost::on_Process_added looping " + row_it[_ModelColumns.col_name]);
			if (row_it[_ModelColumns.col_PID] == PPID ) {
				// When parent process is found, appendit as children and continue
				PRINTD("TreeViewHost::on_Process_added added parent " + process.get__name());
				row = *(_refPtrTreeStore->append(row_it.children()));
				row[_ModelColumns.col_PID] = PID;
				row[_ModelColumns.col_PPID] = PPID;
			  	row[_ModelColumns.col_name] = process.get__name();

/ *				Gtk::TreeStore::Row childrow = *(_refPtrTreeStore->append(row_it.children()));
				childrow[_ModelColumns.col_PID] = PID;
				childrow[_ModelColumns.col_PPID] = PPID;
				childrow[_ModelColumns.col_name] = process.get__name();
* /
			} else if (row_it[_ModelColumns.col_PPID] == PID ) {
				// When a child is found, reparent it and continue
				//TODO NOW
				PRINTD("TreeViewHost::on_Process_added added child " + process.get__name());
				row_it = *(_refPtrTreeStore->append(row.children()));
/ *				Gtk::TreeStore::Row childrow = *(_refPtrTreeStore->append(row_it.children()));
				childrow[_ModelColumns.col_PID] = PID;
				childrow[_ModelColumns.col_PPID] = PPID;
				childrow[_ModelColumns.col_name] = process.get__name();
* /				 
			}
		}
}
*/

/*
 *
 * /
bool TreeViewHost::add_proccess_to_parent(const Gtk::TreeModel::iterator & iter, 
										  const Process & process) 
{
	int PID = process.get__PID();
	int PPID = process.get__PPID();
	
	bool found = false;
	
	Gtk::TreeModel::Row row_it = *iter;

	if (row_it[_ModelColumns.col_PID] == PPID ) {
		// When parent process is found, appendit as children
		PRINTD("TreeViewHost::add_proccess_to_parent parent found " + process.get__name());
		Gtk::TreeStore::Row childrow = *(_refPtrTreeStore->append(row_it.children()));
		childrow[_ModelColumns.col_PID] = PID;
		childrow[_ModelColumns.col_PPID] = PPID;
		childrow[_ModelColumns.col_name] = process.get__name();
		found = true;
	} else if (row_it[_ModelColumns.col_PID] == PID ) {
		// When process exists
		PRINTD("TreeViewHost::add_proccess_to_parent skipped " + process.get__name());
		found = true;
	} else {
		Gtk::TreeStore::Children children = row_it->children();
		Gtk::TreeStore::iterator children_iter;
		for(children_iter = children.begin(); found || children_iter != children.end(); ++children_iter) {
			if (add_proccess_to_parent(children_iter, process)) {
				found = true;
				break;
			}
		}	
	}
	return found;
}*/

void TreeViewHost::on_process_removed(const Process & process) {
	PRINTD("TreeViewHost::on_process_removed " + process.get__name());
	Gtk::TreeStore::iterator process_iter;
//	if ( find_process_from_here (process, root_iter, result_iter) ) {
	if ( find_process (process, process_iter) ) {
		_refPtrTreeStore->erase(process_iter);
		PRINTD("TreeViewHost::on_process_removed process has been removed " + process.get__name());
	}
}

/*
 *
 */
bool TreeViewHost::find_parent_process(const Process & process,
										Gtk::TreeModel::iterator & found_iter)
{
	int PPID = process.get__PPID();
	bool found = false;

	if (PPID == 0) {
		// When parent is kernel
		found_iter = _refPtrTreeStore->children();
		found = true;
	} else {
		Gtk::TreeStore::Children children = _refPtrTreeStore->children();
		Gtk::TreeStore::iterator children_iter;
		for(children_iter = children.begin(); found || children_iter != children.end(); ++children_iter) {
//			if (find_parent_process_from_here(process, children_iter, found_iter)) {
			if (find_process_by_PID_from_here(PPID, children_iter, found_iter)) {
				found = true;
				break;
			}
		}	
	}
	return found;
}

/*
 *
 */
bool TreeViewHost::find_parent_process_from_here(const Process & process,
												  const Gtk::TreeModel::iterator & from_iter,
												  Gtk::TreeModel::iterator & found_iter)
{
	int PPID = process.get__PPID();
	bool found = false;
	Gtk::TreeModel::Row row_it = *from_iter;

	if (row_it[_ModelColumns.col_PID] == PPID ) {
		// When parent process is found
		found_iter = from_iter;
		found = true;
	} else {
		//Keep looking;
		Gtk::TreeStore::Children children = row_it->children();
		Gtk::TreeStore::iterator children_iter;
		for(children_iter = children.begin(); found || children_iter != children.end(); ++children_iter) {
			if (find_parent_process_from_here(process, children_iter, found_iter)) {
				found = true;
				break;
			}
		}	
	}
	return found;
}

/*
 *
 */
bool TreeViewHost::find_process(const Process & process,
								Gtk::TreeModel::iterator & found_iter)
{
	int PID = process.get__PID();
	bool found = false;

	if (PID == 0) {
		// When process is kernel
		//TODO this deserves a warning
		found_iter = _refPtrTreeStore->children();
		found = true;
	} else {
		Gtk::TreeStore::Children children = _refPtrTreeStore->children();
		Gtk::TreeStore::iterator children_iter;
		for(children_iter = children.begin(); found || children_iter != children.end(); ++children_iter) {
//			if (find_process_from_here(process, children_iter, found_iter)) {
			if (find_process_by_PID_from_here(PID, children_iter, found_iter)) {
				found = true;
				break;
			}
		}	
	}
	return found;
}

/*
 *
 */
bool TreeViewHost::find_process_from_here(const Process & process,
										  const Gtk::TreeModel::iterator & from_iter,
										  Gtk::TreeModel::iterator & found_iter)
{
	int PID = process.get__PID();
	bool found = false;
	Gtk::TreeModel::Row row_it = *from_iter;

	if (row_it[_ModelColumns.col_PID] == PID ) {
		// When parent process is found
		PRINTD("TreeViewHost::find_parent_proccess_from_here found " + row_it[_ModelColumns.col_name]);
		found_iter = from_iter;
		found = true;
	} else {
		Gtk::TreeStore::Children children = row_it->children();
		Gtk::TreeStore::iterator children_iter;
		for(children_iter = children.begin(); found || children_iter != children.end(); ++children_iter) {
			if (find_process_from_here(process, children_iter, found_iter)) {
				found = true;
				break;
			}
		}	
	}
	return found;
}


bool TreeViewHost::find_process_by_PID_from_here(int PID,
												  const Gtk::TreeModel::iterator & from_iter,
												  Gtk::TreeModel::iterator & found_iter)
{
	bool found = false;
	Gtk::TreeModel::Row row_it = *from_iter;

	if (row_it[_ModelColumns.col_PID] == PID ) {
		// When process is found
		found_iter = from_iter;
		found = true;
	} else {
		// When process is NOT found, look in next levels
		Gtk::TreeStore::Children children = row_it->children();
		Gtk::TreeStore::iterator children_iter;
		for(children_iter = children.begin(); found || children_iter != children.end(); ++children_iter) {
			if (find_process_by_PID_from_here(PID, children_iter, found_iter)) {
				found = true;
				break;
			}
		}	
	}
	return found;
}

/*
 *
 */
void TreeViewHost::on_treeview_row_activated (const Gtk::TreeModel::Path& path,
											  Gtk::TreeViewColumn*) 
{
	Gtk::TreeModel::iterator iter = _refPtrTreeStore->get_iter(path);
	if (iter) {
		Gtk::TreeModel::Row row = *iter;
		int PID = (*iter)[_ModelColumns.col_PID];
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
			int PID = (*iter)[_ModelColumns.col_PID];
			PRINTD("TreeViewHost::Row activated: ID=");
			PRINTD(PID);
		}
	}
	expand_all();
	show_all_children();
}
