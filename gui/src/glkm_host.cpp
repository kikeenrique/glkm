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

#include <signal.h>

#include "glkm_host.hpp"
#include "debug.hpp"


void Host::niam( int sig )
{
		Host::dispatcher.leave();
}

Host::Host()
{
//		signal(SIGTERM, sigc::mem_fun( *this, &Host::niam) );
//        signal(SIGINT, niam);
   
        DBus::default_dispatcher = &dispatcher;
        DBus::Connection conn = DBus::Connection::SystemBus();
        HalManagerProxy hal(conn); 
        dispatcher.enter();
}

Host::~Host()
{
	//Null
}

