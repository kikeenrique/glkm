/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * hal-device-proxy.hpp
 * Copyright (C) Enrique García Álvarez 2008 <kike+glkm@eldemonionegro.com>
 * 
 * hal-device-proxy.hpp is free software: you can redistribute it and/or modify it
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

#include <giomm/init.h>

#include <iostream>

#include "linux-kernel-monitor-server.hpp"
#include "hal-device-proxy.hpp"

static const char* SERVER_PATH = "/org/freedesktop/Hal/devices/procmon";
static const char* INTERFACE = "org.freedesktop.Hal.Device.LinuxKernelMonitor";

LinuxKernelMonitorServer::LinuxKernelMonitorServer( DBus::Connection& connection )
	: DBus::ObjectAdaptor(connection, SERVER_PATH)
{
	filter = new DBus::Callback <LinuxKernelMonitorServer, bool, const DBus::Message&> 
						(this, &LinuxKernelMonitorServer::handle_message);
	conn().add_filter(filter);
	
	Gio::init();
}

LinuxKernelMonitorServer::~LinuxKernelMonitorServer() {
}

void LinuxKernelMonitorServer::set__device(HalDeviceProxy * value) {
  _device = value;
}

VectorString LinuxKernelMonitorServer::GetAllProcesses(){

	std::cout << "GetAllProcesses" << std::endl;

	VectorString processes;

	std::string sysfs_path;
	sysfs_path = _device->get_property_string("linux.sysfs_path") + "/task_list";
	std::cout << "GetPropertystring :" << sysfs_path << std::endl;
	if (!get_vectorstring_from_sys_file(sysfs_path, processes) ){
		std::cerr << "Error reading sys directory" << std::endl;
	}
	return processes;
}

DBus::String LinuxKernelMonitorServer::Hello( const ::DBus::String& name ){
	return "Hello " + name + "!";
}

/** 
 TODO complete
 *  get_vectorstring_from_sys_file:
 *  @directory:			Directory, e.g. "/sys/class/misc/procmon"
 *  @file:				File, e.g. "task_list"
 *  @result:			A stringlist with the content of file. 
 *						Each line is a string.
 *
 *  Returns:            True if everything went fine.
 *
 *  Get a strlist value from a formatted text file.
 *
 *  Example: Given that the file /sys/class/misc/procmon/task_list contains
 *  the lines
 *
 *    "init [1] - [0]"
 *    "cron [1654] - [1]"
 *    "hald [5820] - [1782]"
 *
 *  then get_vectorstring_from_sys_file ("/sys/class/misc/procmon", "task_list") 
 *  will return a string list with the content of line.
 */

bool LinuxKernelMonitorServer::get_vectorstring_from_sys_file (const std::string & sysfs_path,
															   VectorString & result) 
{
	bool argout = true;

	std::cerr << "get_vectorstring_from_sys_file start opening " << sysfs_path << std::endl;
	try {
		RefPtrFile file = Gio::File::create_for_path(sysfs_path);
		if (!file) {
			std::cerr << "Gio::File::create_for_path() returned an empty RefPtr." << std::endl;
			argout = false;
		}
		RefPtrFileInputStream file_istream = file->read();
		if (!file_istream) {
			std::cerr << "Gio::File::read() returned an empty RefPtr." << std::endl;
			argout = false;			
		}
		RefPtrDataInputStream data_istream = Gio::DataInputStream::create(file_istream);
		if (!data_istream) {
			std::cerr << "Gio::FileInputStream::create() returned an empty RefPtr." << std::endl;
			argout = false;
		}

		std::cerr << "get_vectorstring_from_sys_file start reading " << std::endl;
		std::string line;
		while (data_istream->read_line(line)) {
			if ( !line.empty() ) {
				result.push_back(line);
			}
		}
	} catch(const Glib::Exception& exception) {
		std::cerr << "Exception caught: " << std::endl;
		std::cerr << exception.what() << std::endl;
		argout = false;		
	}

	return argout;
}

