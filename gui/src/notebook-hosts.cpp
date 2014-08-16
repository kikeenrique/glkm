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

#include <glibmm/fileutils.h>

#include "notebook-hosts.hpp"
#include "notebook-page-host.hpp"
#include "host.hpp"

#include "config.h"
#include "debug.hpp"


NotebookHosts::NotebookHosts(BaseObjectType * cobject, const RefPtrBuilder & refBuilder)
	:Gtk::Notebook(cobject),
	_refPtrBuilder(refBuilder)
{
	/*
	signal_page_added().connect(sigc::mem_fun(*this,
											  &NotebookHosts::on_my_page_added) );
	signal_page_removed().connect(sigc::mem_fun(*this,
												&NotebookHosts::on_my_page_removed) );
*/
	//TODO
	//remove first page, at the moment, this is the only way to remove the ""obligatory glade page".
	remove_page();
}

NotebookHosts::~NotebookHosts() {
}

void NotebookHosts::on_host_added(Host * host) {
	add_host_page(*host);
}
/*
void NotebookHosts::on_my_page_added(Gtk::Widget * page, guint page_num) {
//	PRINTD("Switched to tab with index " + page_num);
}

void NotebookHosts::on_my_page_removed(Gtk::Widget * page, guint page_num) {
//	PRINTD("Switched to tab with index " + page_num);
}
*/
void NotebookHosts::add_host_page(Host & host) {
	RefPtrBuilder _refPtrBuilder2;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
	try {
		_refPtrBuilder2 = Gtk::Builder::create_from_file(GLADE_FILE, "notebook_hosts-hpaned");
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
	_refPtrBuilder2 = Gtk::Builder::create_from_file(GLADE_FILE, "notebook_hosts-hpaned", "", error);
	if (error.get()){
		std::cerr << error->what() << std::endl;
		return 1;
	}
#endif //GLIBMM_EXCEPTIONS_ENABLED

	NotebookPageHost * tmp_NotebookPageHost = NULL;
	_refPtrBuilder2->get_widget_derived("notebook_hosts-hpaned", tmp_NotebookPageHost);
	if (tmp_NotebookPageHost){
		tmp_NotebookPageHost->set_my_Host(host);
		//Label showed will be host name
		append_page(*tmp_NotebookPageHost, host.get__hostname());
		show_all_children();
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}
}
