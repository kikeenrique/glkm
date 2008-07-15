/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * hal-device-proxy.cpp
 * Copyright (C) Enrique García Álvarez 2008 <kike+glkm@eldemonionegro.com>
 * 
 * hal-device-proxy.cpp is free software: you can redistribute it and/or modify it
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

#include "hal-device-proxy.hpp"


/**
 */


/** 
 *  @HalDeviceProxy:
 *
 *  General Documentation
 *
 *  HAL Specification URL:
 * 	http://people.freedesktop.org/~david/hal-spec/hal-spec.html#interfaces
 *
 *
 *   Device interface
 *  ------------------
 *	Signal:			PropertyModified
 *	Parameters:		Int num_changes, Array of struct {String property_name,
 *					Bool added, Bool removed}
 *  Description:	One or more properties on the device object have changed.
 *
 *	Signal:			Condition
 *	Parameters:		String name, String details
 *  Description:	A generic mechanism used to specify a device condition that
 *					cannot be expressed in device properties. (NOTE: newly 
 *					written code should use dedicated signals on a dedicated 
 *					interface.).
 *
 *  Returns:
 *
 *  Explanation.
 *
 *
 *  Example:
 *
 */
HalDeviceProxy::HalDeviceProxy(DBus::Connection& connection, const DBus::Path& udi )
:   DBus::InterfaceProxy("org.freedesktop.Hal.Device"),
	DBus::ObjectProxy(connection, udi, "org.freedesktop.Hal") {
	connect_signal(HalDeviceProxy, PropertyModified, on_property_modified);
	connect_signal(HalDeviceProxy, Condition, on_condition);
}


/** 
 *  @~HalDeviceProxy:
 *
 *  Returns:
 *
 *  Explanation.
 *
 *
 *  Example:
 *
 */
HalDeviceProxy::~HalDeviceProxy() {
}


/** 
 *  addon_is_ready:
 *
 *  HAL INFO
 *  ========
 *	Method:			AddonIsReady
 *  Returns:		Bool
 *  Parameters:		-
 *  Throws:			PermissionDenied
 *  Description:	An addon needs to call this method when it's ready for the 
 *					device to be announced on D-Bus. The rationale for this 
 *					method is to allow an addon to modify the device object and
 *					claim interfaces before the device is announced on D-Bus. 
 *
 *  Exceptions:			NoSuchProperty
 *
 *  Example:
 *
 */
DBus::Bool HalDeviceProxy::addon_is_ready() {
	DBus::CallMessage call;
	
	call.member("AddonIsReady");
    
	//declaret out of try. scope solution 
   	DBus::MessageIter it;
	try {
		DBus::Message reply = this->invoke_method(call);
		it = reply.reader();
	}
	catch (const DBus::Error& exception){
		std::cerr << "AddonIsReady" << std::endl;
		std::cerr << exception.what() << std::endl;
		std::cerr << exception.name() << std::endl;
		std::cerr << exception.message() << std::endl;
	}

	DBus::Bool argout;
    it >> argout;

	return argout;	
}

/** 
 *  claim_interface:
 *  @name:
 *  @introspection_xml:
 *
 *  HAL INFO
 *  ======== 				 
 *	Method:			ClaimInterface
 *  Returns:		Bool
 *  Parameters:		String name
 *					String introspection_xml
 *  Throws:			PermissionDenied
 *  Description:	An addon can use this method for making the HAL daemon 
 *					route all D-Bus calls on the given interface to the addon 
 *					via the peer to peer D-Bus connection between the addon and 
 *					the HAL daemon.
 *
 *  Exceptions:		NoSuchProperty
 *
 *  Example:
 *
 */
DBus::Bool HalDeviceProxy::claim_interface(const DBus::String & name,
										   const DBus::String & introspection_xml) {
	DBus::CallMessage call;
	DBus::MessageIter wi = call.writer();
	
	wi << name;
	wi << introspection_xml;

	call.member("ClaimInterface");

	//declaret out of try. scope solution 
   	DBus::MessageIter it;
	try {
			DBus::Message reply = invoke_method(call);
	    	it = reply.reader();
	}
	catch (const DBus::Error& exception){
			std::cerr << "ClaimInterface" << std::endl;
			std::cerr << exception.what() << std::endl;
    		std::cerr << exception.name() << std::endl;
       		std::cerr << exception.message() << std::endl;
	}

	DBus::Bool argout;
    it >> argout;

	return argout;
}

/** 
 *  get_property_string:
 *  @key:
 *
 *  HAL INFO
 *  ========
 *	Method:			GetPropertyString
 *  Returns:		String
 *  Parameters:		String key
 *  Throws:			NoSuchProperty
 *  Description:	Get property
 *
 *
 *  Returns:
 *
 *  Exceptions:			NoSuchProperty
 *
 *  Example:
 *
 */
DBus::String HalDeviceProxy::get_property_string(const DBus::String & key) {
	DBus::CallMessage call;
	DBus::MessageIter wi = call.writer();
	
	wi << key;
	call.member("GetPropertyString");

	//declaret out of try. scope solution 
   	DBus::MessageIter it;
	try {
			DBus::Message reply = invoke_method(call);
			it = reply.reader();
	}
	catch (const DBus::Error& exception){
			std::cerr << "GetPropertyString" << std::endl;
			std::cerr << exception.what() << std::endl;
			std::cerr << exception.name() << std::endl;
       		std::cerr << exception.message() << std::endl;
	}

	DBus::String argout;
	it >> argout;	

	return argout;	
}


/** 
 *  @on_property_modified:
 *  @sig:
 *
 *  Returns:
 *
 *  Explanation.
 *
 *
 *  Example:
 *
 */
void HalDeviceProxy::on_property_modified( const DBus::SignalMessage& sig ) {
	typedef DBus::Struct< DBus::String, DBus::Bool, DBus::Bool > HalProperty;

	DBus::MessageIter it = sig.reader();
	DBus::Int32 number;

	it >> number;
	
	DBus::MessageIter arr = it.recurse();

	for(int i = 0; i < number && !(arr.at_end()); ++i, ++arr)
	{
		HalProperty hp;

		arr >> hp;

		std::cout << "modified property " << hp._1 << " in " << path() << std::endl;
	}
}


/** 
 *  @on_condition:
 *  @sig:
 *
 *  Returns:
 *
 *  Explanation.
 *
 *
 *  Example:
 *
 */
void HalDeviceProxy::on_condition( const DBus::SignalMessage& sig ) {
	DBus::MessageIter it = sig.reader();
	DBus::String condition;

	it >> condition;

	std::cout << "encountered condition " << condition << " in " << path() << std::endl;
}
