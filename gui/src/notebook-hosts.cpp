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

#include "notebook-hosts.hpp"
#include "notebook-page-host.hpp"
#include "host.hpp"

#include "config.h"
#include "debug.hpp"

//TODO temporal
#define GLADE_FILE  "/home/enrgar/svn/pfc/trunk/gui/data/glkm.glade" 

NotebookHosts::NotebookHosts(BaseObjectType * cobject, const RefPtrGladeXml & refGlade)
	:Gtk::Notebook(cobject),
	_refPtrGlademmXml(refGlade)
{
	signal_page_added().connect(sigc::mem_fun(*this,
											  &NotebookHosts::on_my_page_added) );
	signal_page_removed().connect(sigc::mem_fun(*this,
												&NotebookHosts::on_my_page_removed) );

	//remove first page, at the moment, this is the only way to remove the ""obligatory glade page".
	remove_page();
}

NotebookHosts::~NotebookHosts() {
}

void NotebookHosts::on_Host_added(Host * host) {
	add_host_page(*host);
}
/*
void NotebookHosts::update(Subject * s) {
}

void NotebookHosts::update(Subject * s, Argument * arg) {
	add_host_page(*(Host *)arg);
}
*/
void NotebookHosts::on_my_page_added(Gtk::Widget * page, guint page_num) {
//	PRINTD("Switched to tab with index " + page_num);
}

void NotebookHosts::on_my_page_removed(Gtk::Widget * page, guint page_num) {
//	PRINTD("Switched to tab with index " + page_num);
}

void NotebookHosts::add_host_page(Host & host) {
	RefPtrGladeXml _refPtrGlademmXml2;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
	try {
		_refPtrGlademmXml2 = Gnome::Glade::Xml::create(GLADE_FILE, "notebook_hosts-hpaned");
	}
	catch(const Gnome::Glade::XmlError& exception) {
		std::cerr << exception.what() << std::endl;
		throw; 
	}	
#else
	std::auto_ptr<Gnome::Glade::XmlError> error;
	_refPtrGlademmXml2 = Gnome::Glade::Xml::create(GLADE_FILE, "notebook_hosts-hpaned", "", error);
	if (error.get()){
		std::cerr << error->what() << std::endl;
		return 1;
	}
#endif //GLIBMM_EXCEPTIONS_ENABLED

	NotebookPageHost * tmp_NotebookPageHost = NULL;
	_refPtrGlademmXml2->get_widget_derived("notebook_hosts-hpaned", tmp_NotebookPageHost);
	if (tmp_NotebookPageHost){
		tmp_NotebookPageHost->set_my_Host(host);

/*
		/TreeViewHost * tmp_TreeViewHost= NULL;
		tmp_NotebookPageHost->take__pTreeViewHost(tmp_TreeViewHost);
		//Set direct access on tree*view*host to its corresponent model host
		tmp_TreeViewHost->set__pHost(&host);
*/
		//Label showed will be hostname
		append_page(*tmp_NotebookPageHost, host.get__hostname());	
		show_all_children();
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}
}
