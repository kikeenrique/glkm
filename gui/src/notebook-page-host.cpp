/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * gui
 * Copyright (C) Enrique García Álvarez 2008 <kike+glkm@eldemonionegro.com>
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

#include <iostream>

#include "notebook-page-host.hpp"
#include "host.hpp"
#include "tree-view-host.hpp"

NotebookPageHost::NotebookPageHost(BaseObjectType * cobject, const RefPtrGladeXml & refGlade)
	:Gtk::HPaned(cobject),
	_refPtrGlademmXml(refGlade) 
{
	//Set TreeView
	_refPtrGlademmXml->get_widget_derived("notebook_hosts-treeview_host", _pTreeViewHost);
	if (_pTreeViewHost){
	}else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}
}

NotebookPageHost::~NotebookPageHost() {
}

Host * NotebookPageHost::get_my_Host() {
	return _pTreeViewHost->take_Host();
}

void NotebookPageHost::set_my_Host(Host & host) {
	_pTreeViewHost->set__pHost(&host);
	host.signal_process_added.connect( sigc::mem_fun(*_pTreeViewHost,
													 &TreeViewHost::on_process_added));
	host.signal_process_removed.connect( sigc::mem_fun(*_pTreeViewHost,
													 &TreeViewHost::on_process_removed));

}
