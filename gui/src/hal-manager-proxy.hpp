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

#ifndef _HAL_MANAGER_PROXY_HPP
#define _HAL_MANAGER_PROXY_HPP

#include <dbusmm/object.h>
#include <dbusmm/interface.h>
#include <dbusmm/connection.h>
#include <dbusmm/message.h>
#include <dbusmm/types.h>

#include <map>

#include "hal-device-proxy.hpp"
#include "utils.hpp"

class Host;
class HalParser;

class HalManagerProxy : public DBus::ObjectProxy, public DBus::InterfaceProxy {

  public:
	HalManagerProxy(DBus::Connection& connection );
	virtual ~HalManagerProxy();
	bool get_all_processes(Host & host);

  protected:
	std::map<DBus::Path, HalDeviceProxyRefPtr> _devices;
	HalDeviceProxyRefPtr _device;
	
  private:
	VectorString get_all_devices();
	VectorString find_device_by_capability(const DBus::String & capability);
	void on_device_added(const DBus::SignalMessage& sig );
	void on_device_removed(const DBus::SignalMessage& sig );
};

#endif //_HAL_MANAGER_PROXY_HPP
