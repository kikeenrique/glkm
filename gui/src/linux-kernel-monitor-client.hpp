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

#ifndef _LINUX_KERNEL_MONITOR_CLIENT_HPP_
#define _LINUX_KERNEL_MONITOR_CLIENT_HPP_

#include <dbusmm/introspection.h>
#include <dbusmm/object.h>
#include <dbusmm/connection.h>
#include <dbusmm/types.h>


#include "linux-kernel-monitor-client-proxy.hpp"

class Host;
class HalParser;

class LinuxKernelMonitorClient : 
	public org::freedesktop::Hal::Device::LinuxKernelMonitor,
	public DBus::IntrospectableProxy,
	public DBus::ObjectProxy 
{

  public:
	LinuxKernelMonitorClient(DBus::Connection & conn, const DBus::Path & udi);

	bool get_all_processes(Host & host);
};

#endif // _LINUX_KERNEL_MONITOR_CLIENT_HPP_
