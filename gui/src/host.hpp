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


#ifndef _HOST_HPP
#define _HOST_HPP

#include <glibmm/ustring.h>

#include <sigc++/signal.h>

#include <map>

#include "process.hpp"

class Filesystem;
class HalController;

class Host {
  public:
	Host();
	virtual ~Host();
	Host(const Host & source);
	Host & operator=(const Host & source);

	void connect();
	void get_all_processes();
	void add_and_synchronize_process(Process & process);
	void delete_all_not_synchronized();

	void print_processes();

	bool get_process(int PID, Process & process);

	inline const Glib::ustring get__hostname() const;
	void set__hostname(Glib::ustring value);
	void set__ip(Glib::ustring value);
	void set__description(Glib::ustring value);

  protected:
	Glib::ustring _hostname;
	Glib::ustring _ip;	
	Glib::ustring _description;

	Filesystem * _filesystems;
	std::map<int, Process> _task_list;

	HalController * _hal_controller;

//	friend class HalParser;

	typedef sigc::signal<void, Process> type_signal_process_added;
	typedef sigc::signal<void, Process> type_signal_process_removed;

  public:
	type_signal_process_added signal_process_added;
	type_signal_process_removed signal_process_removed;
};
inline const Glib::ustring Host::get__hostname() const {
  return _hostname;
}

#endif // _HOST_HPP
