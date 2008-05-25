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

//#include <signal.h>
#include <dbusmm/dispatcher.h>

#include "hal-controller.hpp"
#include "hal-manager-proxy.hpp"

HalController::HalController():
	_connection(DBus::Connection::SystemBus())
{
//	signal(SIGTERM, sigc::mem_fun( *this, &HalController::niam) );
//	signal(SIGINT, sigc::mem_fun( *this, &HalController::niam));
	_hal_manager = new HalManagerProxy(_connection);
	DBus::default_dispatcher = &_dispatcher;
	_dispatcher.attach(NULL);
	_dispatcher.enter();
}

HalController::~HalController() {
}

bool HalController::update_processes() {
}

void HalController::update_process_info() {
}

void HalController::niam(int sig) {
	_dispatcher.leave();
}
