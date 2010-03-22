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

#ifndef _HOSTS_HPP
#define _HOSTS_HPP

#include <sigc++/signal.h>

#include <glibmm/ustring.h>

#include <map>

#include "host.hpp"

class Hosts{
  public:
  	Hosts();
	virtual ~Hosts();
	bool create_host(const Glib::ustring & hostname, const Glib::ustring & ip, const Glib::ustring & description);

  protected:
	typedef sigc::signal<void, Host *> type_signal_host_added;
	std::map<Glib::ustring, Host> _hosts;

  public:
	type_signal_host_added signal_host_added;
};

#endif // _HOSTS_HPP
