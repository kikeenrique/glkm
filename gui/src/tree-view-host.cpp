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
//#include "host.hpp"
#include "process.hpp"
#include "controller.hpp"

#include "config.h"
#include "debug.hpp"



TreeViewHost::TreeViewHost(BaseObjectType* cobject, const RefPtrBuilder & refBuilder):
	Gtk::TreeView(cobject),
	_refPtrBuilder(refBuilder)
{
	//Create the Tree model
	_refPtrTreeStore = Gtk::TreeStore::create(_ModelColumns);
	set_model(_refPtrTreeStore);

	//Allow multiple selection
	_refPtrTreeSelection = get_selection();
//	_refPtrTreeSelection->set_mode(Gtk::SELECTION_MULTIPLE);
	_refPtrTreeSelection->set_mode(Gtk::SELECTION_SINGLE);

/*	_refPtrTreeSelection->selected_foreach_iter(sigc::mem_fun(*this,
														   &TreeViewHost::on_selected_row_callback) );
*/
	//Connect signal handlers for the treeview "menu popup treeview host" :
//TODO this must be fixed sometime, this is not a proper way to do this	
	RefPtrBuilder _refPtrBuilder2;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
	try {
		_refPtrBuilder2 = Gtk::Builder::create_from_file(GLADE_FILE, "notebook_hosts-treeview_host-menu");
	}
	catch(const Glib::FileError& exception) {
		std::cerr << "FileError: " << exception.what() << std::endl;
		throw;
	}
	catch(const Gtk::BuilderError& exception){
		std::cerr << "BuilderError: " << exception.what() << std::endl;
		throw;
	}
#else
	std::auto_ptr<Glib::Error> error;
	_refPtrBuilder2 = Gtk::Builder::create_from_file(GLADE_FILE, "notebook_hosts-treeview_host-menu", "", error);
	if (error.get()){
		std::cerr << error->what() << std::endl;
		return 1;
	}
#endif //GLIBMM_EXCEPTIONS_ENABLED

	// Get a controller instance that will be used for initialize and connect 
	// signals to members
	Controller& controller = Controller::instance();

	_pMenu_Popup_TreeView_Host = NULL;
	_refPtrBuilder2->get_widget("notebook_hosts-treeview_host-menu", _pMenu_Popup_TreeView_Host);
	if (_pMenu_Popup_TreeView_Host){
	}
	_pMenuitem_Refresh = NULL;
	_refPtrBuilder2->get_widget("notebook_hosts-treeview_host-menu-menuitem-refresh", _pMenuitem_Refresh);
	if (_pMenuitem_Refresh) {
		_pMenuitem_Refresh->signal_activate().connect(sigc::mem_fun(*this,
																	&TreeViewHost::on_menu_popup_refresh) );
		_pMenuitem_Refresh->signal_activate().connect(sigc::mem_fun(controller,
																	&Controller::action_processes_selected) );
	}
/*	
	if (_pMenuitem_Refresh) {
		_pMenuitem_Refresh->signal_activate().connect(sigc::mem_fun(*this,
																	&TreeViewHost::on_menu_popup_refresh) );
	}
*/

	_pMenuitem_ExpandAll = NULL;
	_refPtrBuilder2->get_widget("notebook_hosts-treeview_host-menu-menuitem-refresh", _pMenuitem_ExpandAll);
	if (_pMenuitem_ExpandAll) {
		_pMenuitem_ExpandAll->signal_activate().connect(sigc::mem_fun(*this,
																	&TreeViewHost::on_menu_popup_expand_all) );
	}
	_pMenuitem_ContractAll = NULL;
	_refPtrBuilder2->get_widget("notebook_hosts-treeview_host-menu-menuitem-refresh", _pMenuitem_ContractAll);
	if (_pMenuitem_ContractAll) {
		_pMenuitem_ContractAll->signal_activate().connect(sigc::mem_fun(*this,
																	&TreeViewHost::on_menu_popup_contract_all) );
	}
	
	
	//Add the TreeView's view columns:
	append_column("PID", _ModelColumns.col_PID);
	//TODO take into account that this can be treated like a numeric column
	//append_column_numeric("PID", _ModelColumns.col_PID);
	append_column("Name", _ModelColumns.col_name);
	append_column_editable("Selected", _ModelColumns.col_bool);
	
/*	//Connect signal:
	signal_row_activated().connect(sigc::mem_fun(
								*this,
							    &TreeViewHost::on_treeview_row_activated) );
*/
	show_all_children();
}

TreeViewHost::~TreeViewHost(){
	//Null
}

/*
Host * TreeViewHost::take_Host() {
	return _pHost;
}

void TreeViewHost::set__pHost(Host * value) {
  _pHost = value;
}
*/

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

void TreeViewHost::on_process_removed(const Process & process) {
	PRINTD("TreeViewHost::on_process_removed " + process.get__name());
	Gtk::TreeStore::iterator process_iter;
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
 *
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
*/
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
/*	_refPtrTreeSelection = get_selection();
	if (_refPtrTreeSelection) {
		Gtk::TreeModel::iterator iter = _refPtrTreeSelection->get_selected();
		if (iter) {
			int PID = (*iter)[_ModelColumns.col_PID];
			PRINTD("TreeViewHost::Row activated: ID=");
			PRINTD(PID);
		}
	}
	show_all_children();*/
	PRINTD("TreeViewHost::on_menu_popup_refresh");
}

void TreeViewHost::on_menu_popup_expand_all() {
//	PRINTD("TreeViewHost::on_menu_popup_expand_all");
	expand_all();
//	show_all_children();
}

void TreeViewHost::on_menu_popup_contract_all() {
	//TODO
//	PRINTD("TreeViewHost::on_menu_popup_contract_all");
	collapse_all();
//	show_all_children();
}
