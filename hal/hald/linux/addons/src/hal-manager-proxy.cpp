	/*
 * hal-manager-proxy.cpp
 * Copyright (C) Enrique García Álvarez 2007 <kike+glkm@eldemonionegro.com>
 * 
 * hal-manager-proxy.cpp is free software: you can redistribute it and/or modify it
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

#include "hal-manager-proxy.hpp"
#include "hal-device-proxy.hpp"


/** 
 *  HalManagerProxy:  
 *  @connection:         Bla, bla
 *
 *  Returns:             A stringlist with the content of file. 
 *                       Each line is a string
 *
 *  Get a strlist value from a formatted text file.
 *
 *  Example:
 *      
 * 
 * HAL Manager
 *
 *
	Method			Returns		Parameters		Throws	Description
	------			-------		----------		------  -----------
	FindDeviceByCapability	Objref[]	String capability       -       Finds devices of the given capability. 

	Signal			Parameters		Description
	------			----------		-----------	 
	DeviceAdded     Objref obj			A device was added to the global device list (GDL).
	DeviceRemoved   Objref obj			A device was removed from the global device list (GDL).
 *	 
 */
HalManagerProxy::HalManagerProxy(DBus::Connection& connection ) :
	DBus::InterfaceProxy("org.freedesktop.Hal.Manager"),
	DBus::ObjectProxy(connection, "/org/freedesktop/Hal/Manager", "org.freedesktop.Hal")
{
	connect_signal(HalManagerProxy, DeviceAdded, on_device_added);
	connect_signal(HalManagerProxy, DeviceRemoved, on_device_removed);
}


/** 
 *  ~HalManagerProxy:
 *
 *  Returns:
 *
 *  Exceptions:
 *
 *  Example:
 *
 */
HalManagerProxy::~HalManagerProxy() {
}


/** 
 *  ~get_device_procmon:
 *
 *  Returns:
 *
 *  Exceptions:
 *
 *  Example:
 *
 */
HalDeviceProxy * HalManagerProxy::get_device_procmon() {
	// Get devices that are able to monitor kernel, that should be only our 
        // own "glkm device" (:p)
	VectorString devices = find_device_by_capability("linux-kernel-monitor");
	VectorString::iterator it;
	HalDeviceProxy * device = NULL;
	//Load those devices in our model.
	for(it = devices.begin(); it != devices.end(); ++it) {
		DBus::Path udi = *it;
		if ( udi.find("procmon", 0) != DBus::String::npos ) {
			device = new HalDeviceProxy(conn(), udi);
		}
	}
	return device;
}

/** 
 *  find_device_by_capability:
 *  @capability:
 *
 *  Returns:
 *
 *  Exceptions:			NoSuchProperty
 *
 *  Example:
 *
 */
VectorString HalManagerProxy::find_device_by_capability(const DBus::String & capability) {
    	DBus::CallMessage call;
        DBus::MessageIter wi = call.writer();
        wi << capability;

	call.member("FindDeviceByCapability");

    	//declaret out of try. scope solution 
	DBus::MessageIter it;
    	try {
		DBus::Message reply = invoke_method(call);
		it = reply.reader();
	}
	catch (const DBus::Error& exception){
		std::cerr << "FindDeviceByCapability" << std::endl;
		std::cerr << exception.what() << std::endl;
    		std::cerr << exception.name() << std::endl;
       		std::cerr << exception.message() << std::endl;
	}

	VectorString udis;
	it >> udis;

	return udis;
}


/** 
 *  on_device_added:
 *  @sig:
 *
 *  Returns:
 *
 *  Exceptions:			NoSuchProperty
 *
 *  Example:
 *
 */
void HalManagerProxy::on_device_added(const DBus::SignalMessage & sig) {
	DBus::MessageIter it = sig.reader();
	DBus::String devname;

	it >> devname;

//TODO implement adding device linux-kernel-monitor capable

	DBus::Path udi(devname);
}


/** 
 *  on_device_removed:
 *  @sig:
 *
 *  Returns:
 *
 *  Exceptions:			NoSuchProperty
 *
 *  Example:
 *
 */
void HalManagerProxy::on_device_removed(const DBus::SignalMessage & sig) {

	DBus::MessageIter it = sig.reader();
	DBus::String devname;

//TODO implement deleting device linux-kernel-monitor capable
	it >> devname;
}

