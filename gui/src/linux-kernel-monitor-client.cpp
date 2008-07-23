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

#include <iostream>

#include "linux-kernel-monitor-client.hpp"
#include "host.hpp"
#include "hal-parser.hpp"

#include "config.h"
#include "debug.hpp"

LinuxKernelMonitorClient::LinuxKernelMonitorClient(DBus::Connection & conn, const DBus::Path & udi)
	: DBus::ObjectProxy(conn, udi, "org.freedesktop.Hal") {
}


/** 
 *  get_all_processes:
 *
 *  Returns:
 *
 *  Exceptions:
 *
 *  Example:
 *
 */
bool LinuxKernelMonitorClient::get_all_processes(Host & host) {

	PRINTD ("LinuxKernelMonitorClient() get_all_processes");
	VectorString task_list;
	try {
		task_list = GetAllProcesses();
	} catch (const DBus::Error& exception) {
		std::cerr << exception.what() << std::endl;
   		std::cerr << exception.name() << std::endl;
		std::cerr << exception.message() << std::endl;
	}
	HalParser h;
	h.parse_synchronize_processes (task_list, host);
}
