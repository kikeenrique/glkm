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

#ifndef _NOTEBOOK_PROCESSES_HPP_
#define _NOTEBOOK_PROCESSES_HPP_

#include <gtkmm/notebook.h>
#include <gtkmm/widget.h>

#include "utils.hpp"

class Process;
class NotebookPageProcess;

//Already trackable as inherits from Gtk::Notebook
class NotebookProcesses : public Gtk::Notebook {
  public:
	NotebookProcesses(BaseObjectType * cobject, const RefPtrBuilder & refBuilder);
	virtual ~NotebookProcesses();

	void on_process_monitor_begin(Process * process);
	void on_process_monitor_end(Process * process);

  protected:
	RefPtrBuilder _refPtrBuilder;

//	void on_my_page_added(Gtk::Widget * page, guint page_num);
//	void on_my_page_removed(Gtk::Widget * page, guint page_num);

	void add_process_page(Process & process);
};

#endif // _NOTEBOOK_PROCESSES_HPP_
