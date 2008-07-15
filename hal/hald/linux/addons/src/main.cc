/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) Enrique García Álvarez 2008 <kike+glkm@eldemonionegro.com>
 * 
 * main.cc is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * main.cc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <dbusmm/glib-integration.h>
#include <dbusmm/connection.h>

#include <iostream>
#include <cstdlib>

#include "hal-manager-proxy.hpp"
#include "hal-device-proxy.hpp"
#include "linux-kernel-monitor-server.hpp"
#include "utils.hpp"

int main(int argc, char* argv[])
{

/*
 * Get enviroment variables "coming" from hald
 */
	const char * udi;
	udi = getenv ("UDI");
	if (!udi) {
		std::cerr << "ERR UDI env not defined" << std::endl;
//		return -2;
	}

	const char * address;
	address = getenv ("HALD_DIRECT_ADDR");
	if (!address) {
		std::cerr << "ERR HALD_DIRECT_ADDR env not defined" << std::endl;
//		return -2;
	}


	MainLoopRefPtr _refPtr_MainLoop;
	DBus::Glib::BusDispatcher dispatcher;
	
	_refPtr_MainLoop = Glib::MainLoop::create();
	
	DBus::default_dispatcher = &dispatcher;
	dispatcher.attach(NULL);

/*	
	Get a connection to HAL daemon
*/ 
	DBus::Connection * hald_connection;

	try {
		hald_connection = new DBus::Connection(address);
	}
	catch (const DBus::Error& exception){
		std::cerr << "ERR Connection" << std::endl;
		std::cerr << exception.what() << std::endl;
		std::cerr << exception.name() << std::endl;
		std::cerr << exception.message() << std::endl;
	}
	std::cout << "Addon connected to hal daemon" << std::endl;

/*  
	Get a HAL device with capability 'linux-kernel-monitor' helped by machine HAL
	 manager.
	As it's not clear when to call AddonIsReady, we do it as soon as posible 
	 because is what other addons use as a rule.
*/
	
	HalManagerProxy * hal_manager;
	try {
		hal_manager = new HalManagerProxy(*hald_connection);
	}
	catch (const DBus::Error& exception){
		std::cerr << "ERR HalManagerProxy()" << std::endl;
		std::cerr << exception.what() << std::endl;
		std::cerr << exception.name() << std::endl;
		std::cerr << exception.message() << std::endl;
	}

	HalDeviceProxy * device_procmon;
	try {
		device_procmon = hal_manager->get_device_procmon();
		device_procmon->addon_is_ready();
	}
	catch (const DBus::Error& exception){
		std::cerr << "ERR: AddonIsReady" << std::endl;
		std::cerr << exception.what() << std::endl;
		std::cerr << exception.name() << std::endl;
		std::cerr << exception.message() << std::endl;
	}

/*
	Now we need to claim interface for making the HAL daemon route all D-Bus 
	 calls on the given interface to our addon via the peer to peer D-Bus 
	 connection between the addon and the HAL daemon. 

	TODO complete info about interface
	The interface we are going to claim is availabe under a xml file.
	VectorString GetAllProcesses ();
	void	Hello (DBus::String Hello_string);
*/
	device_procmon->claim_interface(
		"org.freedesktop.Hal.Device.LinuxKernelMonitor",
		"    <method name=\"GetAllProcesses\">\n"
		"      <arg type=\"as\" name=\"return_code\" direction=\"out\"/>\n"
		"    </method>\n"
		"    <method name=\"Hello\">\n"
		"      <arg type=\"s\" name=\"name\" direction=\"in\"/>\n"
		"      <arg type=\"s\" name=\"greeting\" direction=\"out\"/>\n"
		"    </method>\n");

/*
	Latest step is to stablish a D-Bus filter in our connection to HAL, so 
	 we only manage messages we now how to manage.

	TODO Still need to know for sure why is not possible to use the 
	 Connection.request_name method.
	One possibility is that hal owns org.freedesktop.Hal and that's why you 
	 cannot request anything under it. Hal instead provides a claim method that
	 redirects D-Bus request to processes that has claimed interfaces.

*/
	LinuxKernelMonitorServer server_lkm(*hald_connection);

	//TODO deferring this set is highly risky and can lead to a crash
	server_lkm.set__device(device_procmon);


/* 
 *	 main loop run
 */
	_refPtr_MainLoop->run();

	return 0;
}
