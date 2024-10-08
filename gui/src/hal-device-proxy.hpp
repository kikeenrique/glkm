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

#ifndef _HAL_DEVICE_PROXY_HPP
#define _HAL_DEVICE_PROXY_HPP

#include <dbusmm/connection.h>
#include <dbusmm/types.h>
#include <dbusmm/error.h>
#include <dbusmm/message.h>
#include <dbusmm/interface.h>
#include <dbusmm/object.h>
#include <dbusmm/util.h>

#include "utils.hpp"

class HalDeviceProxy: 
	public DBus::InterfaceProxy,
	public DBus::ObjectProxy
{

public:
	HalDeviceProxy(DBus::Connection & connection, const DBus::Path & udi );
	virtual ~HalDeviceProxy();

	DBus::String get_property_string(const DBus::String & key);
	VectorString get_property_string_list(const DBus::String & key);
	bool rescan();
	bool get_all_properties() throw(DBus::Error);

private:
	void on_property_modified(const DBus::SignalMessage & sig );
	void on_condition( const DBus::SignalMessage & sig );
	
protected:
	DictVariable _properties;

};

typedef DBus::RefPtr<HalDeviceProxy> HalDeviceProxyRefPtr;

#endif // _HAL_DEVICE_PROXY_HPP
