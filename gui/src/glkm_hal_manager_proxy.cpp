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

#include <signal.h>
#include <iostream>

#include "debug.hpp"
#include "glkm_hal_manager_proxy.hpp"


#define DBUS_TYPE_STRUCT        ((int) 'r')
#define DBUS_TYPE_STRING        ((int) 's')
#define DBUS_TYPE_ARRAY         ((int) 'a')
#define DBUS_TYPE_VARIANT       ((int) 'v')
#define DBUS_TYPE_DICT_ENTRY    ((int) 'e')

/** 
 *  HalManagerProxy:  
 *  @connection:         Bla, bla
 *  @file:               File, e.g. "procmon"
 *
 *  Returns:             A stringlist with the content of file. 
 *                       Each line is a string
 *
 *  Get a strlist value from a formatted text file.
 *
 *  Example: Given that the file /sys/class/misc/procmon contains
 *  the lines
 *
 *    "init [1] - [0]"
 *    "cron [1654] - [1]"
 *    "hald [5820] - [1782]"
 *
 *  then hal_util_get_strlist_from_file ("/sys/class/misc", "procmon") 
 *  will return a string list with the content of line.
 *
 *      
 * 
 * HAL Manager
 *
 *
	Method			Returns		Parameters	Throws	Description
	------			-------		----------	------  -----------
	GetAllDevices   Objref[]					Get all UDI's in the database.
     
	Signal			Parameters		Description
	------			----------		-----------	 
	DeviceAdded     Objref obj			A device was added to the global device list (GDL).
	DeviceRemoved   Objref obj			A device was removed from the global device list (GDL).
 *	 
 */

HalManagerProxy::HalManagerProxy( DBus::Connection& connection )
: DBus::InterfaceProxy("org.freedesktop.Hal.Manager"),
  DBus::ObjectProxy(connection, "/org/freedesktop/Hal/Manager", "org.freedesktop.Hal")
{
	connect_signal(HalManagerProxy, DeviceAdded, DeviceAddedCb);
	connect_signal(HalManagerProxy, DeviceRemoved, DeviceRemovedCb);

	std::vector< DBus::String > devices = GetAllDevices();
	std::vector< DBus::String >::iterator it;
	for(it = devices.begin(); it != devices.end(); ++it) {
		DBus::Path udi = *it;
		_devices[udi] = new HalDeviceProxy(connection, udi);

		if ( udi.find("proc", 0) != DBus::String::npos ) {
			std::cout << "procmon device " << udi << std::endl;
/*			std::cout << "device properties: " << std::endl;
			std::map< DBus::String, DBus::Variant > properties = HalDeviceProxy::GetAllProterties(_devices[udi]);
			std::map< DBus::String, DBus::Variant >::iterator it_properties;
			for(it_properties = properties.begin(); it_properties != properties.end(); ++it_properties){
				std::cout << '\t' << "[" << it_properties->first << "->";
				std::cout << it_properties->second;
				std::cout << "]" << std::endl;
			}
*/
		} else {
			std::cout << "found device " << udi << std::endl;
		}
	}
}

std::vector< DBus::String > HalManagerProxy::GetAllDevices()
{
	std::vector< DBus::String > udis;
	DBus::CallMessage call;

	call.member("GetAllDevices");

	DBus::Message reply = invoke_method(call);
	DBus::MessageIter it = reply.reader();

	it >> udis;
	return udis;
}

void HalManagerProxy::DeviceAddedCb( const DBus::SignalMessage& sig )
{
	DBus::MessageIter it = sig.reader();
	DBus::String devname;

	it >> devname;

	DBus::Path udi(devname);

	_devices[devname] = new HalDeviceProxy(conn(), udi);
	std::cout << "added device " << udi << std::endl;
}

void HalManagerProxy::DeviceRemovedCb( const DBus::SignalMessage& sig )
{
	DBus::MessageIter it = sig.reader();
	DBus::String devname;

	it >> devname;

	std::cout << "removed device " << devname << std::endl;

	_devices.erase(devname);
}

