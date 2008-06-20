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

//TODO further investigation
//#include <signal.h>

#include <iostream>

#include "hal-controller.hpp"
#include "hal-manager-proxy.hpp"
#include "host.hpp"

HalController::HalController():
//	_connection(DBus::Connection::SystemBus())
	_dispatcher()
{
//TODO further investigation 
//      signal(SIGTERM, sigc::mem_fun( *this, &HalController::niam) );
//      signal(SIGINT, sigc::mem_fun( *this, &HalController::niam));
	DBus::default_dispatcher = &_dispatcher;
	//attached by default to glib main context
	_dispatcher.attach(NULL);
	try {
		_connection = new DBus::Connection(DBus::Connection::SystemBus());
	}
	catch (const DBus::Error& exception){
		std::cerr << "Connection" << std::endl;
		std::cerr << exception.what() << std::endl;
    		std::cerr << exception.name() << std::endl;
       		std::cerr << exception.message() << std::endl;
	}

	/*
	dbusmm Connection seems to use dbus_bus_get_private() to get a system 
	bus connection. And as DBUS api doc version 1.2.1 says 
	"This function calls dbus_connection_set_exit_on_disconnect() on the
	new connection, so the application will exit if the connection closes.
	You can undo this by calling dbus_connection_set_exit_on_disconnect()
	yourself after you get the connection."
	*/
	_connection->exit_on_disconnect (false);
	_hal_manager = new HalManagerProxy(*_connection);
}

HalController::~HalController() {
	_dispatcher.leave();
	_connection->disconnect();
	//TODO threat halmanagerproxy pointer, for example    
}

bool HalController::get_all_processes(Host & host) {
	return _hal_manager->get_all_processes(host);
}
