/*
 * gui
 * Copyright (C) Enrique García Álvarez 2007 <kike+glkm@eldemonionegro.com>
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

#ifndef GLKM_HAL_MANAGER_PROXY_HPP
#define GLKM_HAL_MANAGER_PROXY_HPP

#include <dbusmm/dbus.h>
//#include <dbusmm/glib-integration.h>
#include <vector>
#include <map>

#include "config.h"
#include "glkm_hal_device_proxy.hpp"


class HalManagerProxy: 
	public DBus::InterfaceProxy,
	public DBus::ObjectProxy
{
public:

	HalManagerProxy( DBus::Connection& connection );

	std::vector< DBus::String > GetAllDevices();

	
private:

	void DeviceAddedCb( const DBus::SignalMessage& sig );
	void DeviceRemovedCb( const DBus::SignalMessage& sig );

	std::map< DBus::String, DBus::RefPtr< HalDeviceProxy > > _devices;
};


#endif//GLKM_HAL_MANAGER_PROXY_HPP
