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

#ifndef _NOTEBOOK_PAGE_HOST_HPP
#define _NOTEBOOK_PAGE_HOST_HPP

#include <gtkmm/paned.h>

#include "tree-view-host.hpp"
#include "utils.hpp"

class Host;
//class TreeViewHost;
class NotebookProcesses;

class NotebookPageHost : public Gtk::HPaned {
  public:
	NotebookPageHost(BaseObjectType * cobject, const RefPtrBuilder & refBuilder);
	virtual ~NotebookPageHost();

	Host * get_my_Host();
	void set_my_Host(Host & host);
	inline TreeViewHost * get__pTreeViewHost();

  protected:
	RefPtrBuilder _refPtrBuilder;
	TreeViewHost * _pTreeViewHost;
	NotebookProcesses * _pNotebookProcesses;

	Host * _pHost;
};

inline TreeViewHost * NotebookPageHost::get__pTreeViewHost(){
  return _pTreeViewHost;
}

#endif // _NOTEBOOK_PAGE_HOST_HPP
