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

#ifndef _HAL_CONTROLLER_HPP
#define _HAL_CONTROLLER_HPP

#include <dbusmm/glib-integration.h>
#include <dbusmm/connection.h>

class Host;
class HalManagerProxy;
class LinuxKernelMonitorClient;

class HalController {
  public:
	HalController();
	virtual ~HalController();
	bool get_all_processes(Host & host);

  protected:
	DBus::Connection * _connection;
	HalManagerProxy * _hal_manager;
	DBus::Glib::BusDispatcher _dispatcher;

  private:
	LinuxKernelMonitorClient * _lkm_client;
};

#endif // _HAL_CONTROLER_HPP
