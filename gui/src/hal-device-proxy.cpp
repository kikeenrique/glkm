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

#include "hal-device-proxy.hpp"

#include "config.h"
#include "debug.hpp"


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
 *  get_property_string_list:
 *  @key:
 *
 *  HAL INFO
 *  ========
 *
 *	Method:			GetPropertyStringList
 *  Returns:		String[]
 *  Parameters:		String key
 *  Throws:			NoSuchProperty, TypeMismatch
 *  Description:	Get property
 *
 *
 *  Returns:
 *
 *  Exceptions:			NoSuchProperty, TypeMismatch
 *
 *  Example:
 *
 */
VectorString HalDeviceProxy::get_property_string_list(const DBus::String & key) {
	DBus::CallMessage call;
	DBus::MessageIter wi = call.writer();
	
	wi << key;
	call.member("GetPropertyStringList");

	//declaret out of try. scope solution 
   	DBus::MessageIter it;
	try {
			DBus::Message reply = invoke_method(call);
	    	it = reply.reader();
	}
	catch (const DBus::Error& exception){
			std::cerr << "GetPropertyStringList" << std::endl;
			std::cerr << exception.what() << std::endl;
    		std::cerr << exception.name() << std::endl;
       		std::cerr << exception.message() << std::endl;
	}

	VectorString argout;
    it >> argout;

	return argout;	
}

/** 
 *  @rescan:
 *
 *  HAL INFO
 *  ========
 *
 *	Method:			Rescan
 *  Returns:		Bool
 *  Parameters:		
 *  Throws:			PermissionDenied
 *  Description:	Force an updates of the properties of a device object by 
 *                  rereading data that is not monitored for changes. 
 *
 *
 *  Returns:
 *           true in case all properpies have been received, false in any other
 *           case.
 *  
 *  Example:
 *
 *
 */
bool HalDeviceProxy::rescan() {
	DBus::CallMessage call;

	call.member("Rescan");

	//declaret out of try. scope solution 
   	DBus::MessageIter it;
	try {
			DBus::Message reply = invoke_method(call);
	    	it = reply.reader();
	}
	catch (const DBus::Error& exception){
			std::cerr << "Rescan" << std::endl;
			std::cerr << exception.what() << std::endl;
    		std::cerr << exception.name() << std::endl;
       		std::cerr << exception.message() << std::endl;
	}

	DBus::Bool argout;
    it >> argout;

	return argout;	
}

/** 
 *  @get_all_properties:
 *
 *  HAL INFO
 *  ========
 *
 *	Method:			GetAllProterties
 *  Returns:		type = a{sv} -> an array of dict entry
 *					(which DBus protocol suggest as a map, hash table or dict object)
 *  Parameters:		- 
 *  Throws:			??
 *  Description:	Get all properties of a device
 *
 *  Returns:
 *           true in case all properpies have been received, false in any other
 *           case.
 *  
 *  Example:
 *
 *          This example shows how to print all key -> properties values that
 *          a device possesses
 *
 *             DictVariable properties = HalDeviceProxy::GetAllProterties(_devices[udi]);
 *             DictVariable::iterator it_properties;
 *             for(it_properties = properties.begin(); it_properties != properties.end(); ++it_properties) {
 *                std::cout << '\t' << "[" << it_properties->first << "->";
 *                std::cout << it_properties->second;
 *                std::cout << "]" << std::endl;
 *             }
 *
 */
bool HalDeviceProxy::get_all_properties() throw(DBus::Error) {
	DBus::CallMessage call;
	bool ok=false;
	
	call.member("GetAllProperties");
    
	try {
		DBus::Message reply = this->invoke_method(call);
		DBus::MessageIter it = reply.reader();
	    
		it >> _properties;
		ok=true;
	}
	catch (const DBus::Error& exception){
		std::cerr << "GetAllProperties" << std::endl;
		std::cerr << exception.what() << std::endl;
		std::cerr << exception.name() << std::endl;
		std::cerr << exception.message() << std::endl;
	}

	return ok;
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
