/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * hal-device-proxy.hpp
 * Copyright (C) Enrique García Álvarez 2008 <kike+glkm@eldemonionegro.com>
 * 
 * hal-device-proxy.hpp is free software: you can redistribute it and/or modify it
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

#ifndef _HAL_DEVICE_LINUXKERNELMONITOR_SERVER_H
#define _HAL_DEVICE_LINUXKERNELMONITOR_SERVER_H

#include <dbusmm/introspection.h>
#include <dbusmm/object.h>
#include <dbusmm/connection.h>
#include <dbusmm/types.h>

#include <string>

#include "linux-kernel-monitor-server-adaptor.hpp"
#include "utils.hpp"

class HalDeviceProxy;

class LinuxKernelMonitorServer
: public org::freedesktop::Hal::Device::LinuxKernelMonitor,
  public DBus::IntrospectableAdaptor,
  public DBus::ObjectAdaptor
{
public:

	LinuxKernelMonitorServer( DBus::Connection& connection );
	~LinuxKernelMonitorServer();
	
	void set__device(HalDeviceProxy * value);

	VectorString GetAllProcesses();
	DBus::String Hello( const DBus::String& name );

	DBus::MessageSlot filter;

  protected:
	bool get_vectorstring_from_sys_file(const std::string & directory, VectorString & result);
	HalDeviceProxy * _device;
};

#endif//_HAL_DEVICE_LINUXKERNELMONITOR_SERVER_H
