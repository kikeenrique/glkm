/*
 * hal-manager-proxy.hpp
 * Copyright (C) Enrique García Álvarez 2007 <kike+glkm@eldemonionegro.com>
 * 
 * hal-manager-proxy.hpp is free software: you can redistribute it and/or modify it
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

#ifndef _HAL_MANAGER_PROXY_HPP
#define _HAL_MANAGER_PROXY_HPP

#include <dbusmm/object.h>
#include <dbusmm/interface.h>
#include <dbusmm/connection.h>
#include <dbusmm/message.h>
#include <dbusmm/types.h>

#include "utils.hpp"


class HalDeviceProxy;

class HalManagerProxy : public DBus::ObjectProxy, public DBus::InterfaceProxy {

  public:
	HalManagerProxy(DBus::Connection& connection );
	~HalManagerProxy();

	HalDeviceProxy * get_device_procmon();
		
  private:
	VectorString find_device_by_capability(const DBus::String & capability);
	void on_device_added(const DBus::SignalMessage& sig );
	void on_device_removed(const DBus::SignalMessage& sig );
};

#endif //_HAL_MANAGER_PROXY_HPP
