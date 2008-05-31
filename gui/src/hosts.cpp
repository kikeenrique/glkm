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

#include "hosts.hpp"
#include "host.hpp"

#include "config.h"
#include "debug.hpp"

Hosts::Hosts() {
}

Hosts::~Hosts() {
}

bool Hosts::create_host(const Glib::ustring & hostname, const Glib::ustring & ip, const Glib::ustring & description) {
	std::map<Glib::ustring, Host>::iterator it;
	bool create=false;
	
	// Search for element with a value of hostname and returns an iterator to it
	// if found, otherwise it returns an iterator to map::end (the
	// element past the end of the container).
	it = _hosts.find(hostname);
	if ( it == _hosts.end() ) {
		//Host does not exists so we have to add it
		create = true;
		Host temp;
		temp.set__hostname(hostname);
		temp.set__ip(ip);
		temp.set__description(description);
		_hosts[hostname] = temp;
		PRINTD("Hosts:: Host added " + _hosts[hostname].get__hostname());
	}

	return create;
}
