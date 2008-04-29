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

#include <signal.h>
#include <iostream>

#include "glkm_hal_device_proxy.hpp"
#include "debug.hpp"


/*
	HAL Specification URL:
	http://people.freedesktop.org/~david/hal-spec/hal-spec.html#interfaces
 */

/*
 * Device
 *
 *		   
	Signal				Parameters					Description
	------				----------					-----------
	PropertyModified	Int num_changes,			One or more properties 
						Array of struct	    		on the device object 
						{String property_name,		have changed.
						Bool added, Bool removed}
 *
 */
HalDeviceProxy::HalDeviceProxy( DBus::Connection& connection, DBus::Path& udi )
: DBus::InterfaceProxy("org.freedesktop.Hal.Device"),
  DBus::ObjectProxy(connection, udi, "org.freedesktop.Hal")
{
	connect_signal(HalDeviceProxy, PropertyModified, PropertyModifiedCb);
	connect_signal(HalDeviceProxy, Condition, ConditionCb);
}

/** 
 *  GetProperty:
 *  @key:         Example "misc.task_list"
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
 *
 *
	Method		Returns		Parameters	Throws		Description
	------		-------		----------	------		-----------
	GetProperty	Variant		String key	NoSuchProperty  Get property. 
     
 *	 
 */
DBus::Variant HalDeviceProxy::GetProperty(DBus::String key)
{
}

/*
 * GetAllProterties  returns  type = a{sv} -> an array of dict entry 
 * (which DBus protocol suggest as a map, hash table or dict object)
 */
std::map< DBus::String, DBus::Variant > HalDeviceProxy::GetAllProterties(DBus::RefPtr< HalDeviceProxy > device)
{
   	std::map< DBus::String, DBus::Variant >  properties;
	DBus::CallMessage call;

	call.member("GetAllProperties");
    
	try {
		DBus::Message reply = device->invoke_method(call);
	    	DBus::MessageIter it = reply.reader();
	    
    		it >> properties;

/*		if ( it.is_dict() == true ) {
			std::cout << "TRUE" << std::endl;
		} else {
			std::cout << "FALSE" << std::endl;
		}
		std::cout << it.signature() << std::endl;	     
     		switch ( it.array_type() ) {
	                case DBUS_TYPE_VARIANT:
				std::cout << "variant" << std::endl;
	                case DBUS_TYPE_STRING:
				std::cout << "string" << std::endl;
	                case DBUS_TYPE_STRUCT:
				std::cout << "struct" << std::endl;
	                case DBUS_TYPE_DICT_ENTRY:
				std::cout << "dict entry" << std::endl;			
			default :
    				std::cout << "nothing" << std::endl;
			;
		}
*/	    
	}
	catch (const DBus::Error& exception){
		std::cerr << exception.what() << std::endl;
    		std::cerr << exception.name() << std::endl;
       		std::cerr << exception.message() << std::endl;
	}

	return properties;
}

void HalDeviceProxy::PropertyModifiedCb( const DBus::SignalMessage& sig )
{
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

void HalDeviceProxy::ConditionCb( const DBus::SignalMessage& sig )
{
	DBus::MessageIter it = sig.reader();
	DBus::String condition;

	it >> condition;

	std::cout << "encountered condition " << condition << " in " << path() << std::endl;
}
