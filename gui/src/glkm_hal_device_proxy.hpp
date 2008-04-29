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

#ifndef _GLKM_HAL_DEVICE_PROXY_HPP_
#define _GLKM_HAL_DEVICE_PROXY_HPP_

#include <dbusmm/dbus.h>
//#include <dbusmm/glib-integration.h>

#include "config.h"


class HalDeviceProxy: 
	public DBus::InterfaceProxy,
	public DBus::ObjectProxy
{
public:

	HalDeviceProxy( DBus::Connection& connection, DBus::Path& udi );
	DBus::Variant GetProperty(DBus::String key);
	std::map< DBus::String, DBus::Variant > GetAllProterties (DBus::RefPtr<HalDeviceProxy>);
	
protected:

private:

	void PropertyModifiedCb( const DBus::SignalMessage& sig );
	void ConditionCb( const DBus::SignalMessage& sig );
};

#endif // _GLKM_HAL_DEVICE_PROXY_HPP_
