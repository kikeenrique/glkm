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

#include <map>

#include "observer.hpp"

class Process;
class Filesystem;
class HalController;

class Host : public Subject {
  public:
	Host();
	virtual ~Host();
	Host(const Host & source);
	Host & operator=(const Host & source);

	inline const Glib::ustring get__hostname() const;
	void set__hostname(Glib::ustring value);
	void set__ip(Glib::ustring value);
	void set__description(Glib::ustring value);

	bool get_process(int PID, Process & process);

  protected:
	Glib::ustring _hostname;
	Glib::ustring _ip;	
	Glib::ustring _description;

	Filesystem * filesystems;
	std::map<int, Process> task_list;

	HalController * hal_controler;
};
inline const Glib::ustring Host::get__hostname() const {
  return _hostname;
}

#endif // _HOST_HPP
