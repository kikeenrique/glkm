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

#include "notebook-processes.hpp"
#include "process.hpp"
#include "notebook-page-process.hpp"

#include "config.h"
#include "debug.hpp"



NotebookProcesses::NotebookProcesses(BaseObjectType * cobject, const RefPtrBuilder & refBuilder):
	Gtk::Notebook(cobject),
	_refPtrBuilder(refBuilder)
{
	//TODO
	//remove first page, at the moment, this is the only way to remove the ""obligatory glade page".
	remove_page();
}

NotebookProcesses::~NotebookProcesses() {
}

void NotebookProcesses::on_process_monitor_begin(Process * process) {
	add_process_page(*process);
}

void NotebookProcesses::on_process_monitor_end(Process * process) {
}
/*
void NotebookProcesses::on_process_monitor_begin(const Process & process){
	add_process_page(process);
}
void NotebookProcesses::on_process_monitor_end(const Process & process){
}
*/
/*
void NotebookProcesses::on_my_page_added(Gtk::Widget * page, guint page_num) {
}

void NotebookProcesses::on_my_page_removed(Gtk::Widget * page, guint page_num) {
}
*/
void NotebookProcesses::add_process_page(Process & process) {
	RefPtrBuilder _refPtrBuilder2;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
	try {
		_refPtrBuilder2 = Gtk::Builder::create_from_file(GLADE_FILE, "notebook_hosts-notebook_processes-vbox");
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
	_refPtrBuilder2 = Gtk::Builder::create_from_file(GLADE_FILE, "notebook_hosts-notebook_processes-vbox", "", error);
	if (error.get()){
		std::cerr << error->what() << std::endl;
		return 1;
	}
#endif //GLIBMM_EXCEPTIONS_ENABLED

	NotebookPageProcess * tmp_NotebookPageProcess = NULL;
	_refPtrBuilder2->get_widget_derived("notebook_hosts-notebook_processes-vbox", tmp_NotebookPageProcess);
	if (tmp_NotebookPageProcess){
//		process.signal_process_updated().connect(sigc::mem_fun(*tmp_NotebookPageProcess,
	//														   &NotebookPageProcess::on_process_updated) );

		//Label showed will be process name
		append_page(*tmp_NotebookPageProcess, process.get__name());
		show_all_children();
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}
}
