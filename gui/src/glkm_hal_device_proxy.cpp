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


#include <dbusmm/connection.h>
#include <dbusmm/types.h>
#include <dbusmm/message.h>

#include <iostream>

#include "glkm_hal_device_proxy.hpp"
#include "debug.hpp"
#include "config.h"


/**
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
 *	Method:			GetProperty
 *  Returns:		Variant      
 *  Parameters:		String key
 *  Throws:			NoSuchProperty
 *  Description:	Get property
 *
 *	Method:			GetAllProterties
 *  Returns:		type = a{sv} -> an array of dict entry
 *					(which DBus protocol suggest as a map, hash table or dict object)
 *  Parameters:		- 
 *  Throws:			??
 *  Description:	Get all properties of a device
 *
 */


/** 
 *  @name:
 *  @param:
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
 *  @name:
 *  @param:
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
 *  get_property:
 *  @key:
 *
 *  Returns:
 *
 *  Exceptions:			NoSuchProperty
 *
 *  Example:
 *
 */
DBus::Variant HalDeviceProxy::get_property(const DBus::String & key) {
	DBus::CallMessage call;
	DBus::MessageIter wi = call.writer();
	
	wi << key;
	call.member("GetProperty");

	//declaret out of try. scope solution 
   	DBus::MessageIter it;
	try {
			DBus::Message reply = invoke_method(call);
	    	it = reply.reader();
	}
	catch (const DBus::Error& exception){
		std::cerr << exception.what() << std::endl;
    		std::cerr << exception.name() << std::endl;
       		std::cerr << exception.message() << std::endl;
	}

	DBus::Variant argout;
    it >> argout;
//some _properties stuff
	return argout;	
}


/** 
 *  @name:
 *  @param:
 *
 *  Returns:
 *
 *  
 *
 *
 *  Example:
 *
 */
bool HalDeviceProxy::update_all_properties() {
	DBus::CallMessage call;
	bool ok=false;
	
	call.member("GetAllProperties");
    
	try {
			DBus::Message reply = this->invoke_method(call);
	    	DBus::MessageIter it = reply.reader();
	    
    		it >> _properties;
	}
	catch (const DBus::Error& exception){
		std::cerr << exception.what() << std::endl;
    		std::cerr << exception.name() << std::endl;
       		std::cerr << exception.message() << std::endl;
	}
//TODO ok must be treated correctly
	return ok;
}


/** 
 *  @name:
 *  @param:
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
	
	PRINTD("total modified properties " + number);
	
	DBus::MessageIter arr = it.recurse();

	for(int i = 0; i < number && !(arr.at_end()); ++i, ++arr)
	{
		HalProperty hp;

		arr >> hp;

		std::cout << "modified property " << hp._1 << " in " << path() << std::endl;
	}
}


/** 
 *  @name:
 *  @param:
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
