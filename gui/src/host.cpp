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

#include "host.hpp"
#include "filesystem.hpp"
#include "hal-controller.hpp"

#include "config.h"
#include "debug.hpp"

Host::Host() {
	_hal_controller = NULL;
	_filesystems = NULL;
}

Host::~Host() {
	//Null
	PRINTD ("~Host() ");
}

Host::Host(const Host & source) :
	_hostname(source._hostname),
	_ip(source._ip),
	_description(source._description),
	_filesystems(source._filesystems),
    _hal_controller(source._hal_controller)
{
	PRINTD ("Host() copy ");
}

Host & Host::operator=(const Host & source) {
	_hostname = source._hostname;
	_ip = source._ip;
	_description = source._description;
	_hal_controller = source._hal_controller;
	_filesystems = source._filesystems;
	PRINTD ("Host() asignation ");

	return *this;
}

void Host::connect (){
	//connected means hal_controler != NULL
	if (_hal_controller==NULL){
		PRINTD ("Host:: beginning hal connection ");
		

		try {
			_hal_controller = new HalController ();
		}
		catch (const DBus::Error& exception){
			std::cerr << "Host(): Connection" << std::endl;
			std::cerr << exception.what() << std::endl;
	   		std::cerr << exception.name() << std::endl;
       		std::cerr << exception.message() << std::endl;
			PRINTD ("Host:: error connecting to host" + _hostname);
		}
	} else {
		PRINTD ("Host:: already connected " + _hostname);
	}
}

void Host::get_all_processes() {

	PRINTD ("Host:: getting processes " + _hostname);

	if (_hal_controller) {
		bool gotten_all = _hal_controller->get_all_processes(*this);
		if (!gotten_all) {
			PRINTD ("Host:: Some problems occur while getting all processes");
		}
	} else {
		PRINTD ("Host:: nothing done, not existent hal connection to " + _hostname);
	}
}

void Host::add_and_synchronize_process(Process & process) {
	
	int PID = process.get__PID();

	// Search for element with a value of PID and returns an iterator to it
	// if found. Otherwise it returns an iterator to map::end (the
	// element past the end of the container).
	std::map<int, Process>::iterator process_iterator;
	process_iterator = _task_list.find(PID);
	if ( process_iterator == _task_list.end() ) {
		//Process does not exists so we have to add it
		_task_list[PID] = process;
		_task_list[PID].set__synchronized(true);

		PRINTD("Host:: process added and sync " + _task_list[PID].get__name());
		signal_process_added.emit(_task_list[PID]);
	} else {
		//Process exists so we just mark it as synchonized
		PRINTD("Host:: process synchronized " + _task_list[PID].get__name());
		_task_list[PID].set__synchronized(true);
	}
}

void Host::delete_all_not_synchronized() {

	std::map<int, Process>::iterator process_iterator;
	for(process_iterator = _task_list.begin(); process_iterator != _task_list.end(); ) {
		bool synchronized = (*process_iterator).second.get__synchronized();
		if (synchronized) {
			(*process_iterator).second.set__synchronized(false);
			++process_iterator;
		} else {
			PRINTD("Host:: process removed " + (*process_iterator).second.get__name());
			signal_process_removed.emit( (*process_iterator).second );
			_task_list.erase(process_iterator++);
		}
	}
/*	for(process_iterator = _task_list.begin(); process_iterator != _task_list.end(); ++process_iterator) {
		(*process_iterator).second.set__synchronized(false);
	}*/

}

bool Host::get_process(int PID, Process & process){
	bool ret=true;

	// Search for element with a value of PID and returns an iterator to it
	// if found. Otherwise it returns an iterator to map::end (the
	// element past the end of the container).
	std::map<int, Process>::iterator process_iterator;
	process_iterator = _task_list.find(PID);
	if ( process_iterator == _task_list.end() ) {
		//Process does not exists 
		ret = false;
	} else {
		//Process exists so we just mark it as synchonized
		PRINTD("Host:: get_process " + _task_list[PID].get__name());
		process = _task_list[PID];
	}

	return ret;
}

void Host::set__hostname(Glib::ustring value) {
  _hostname = value;
}

void Host::set__ip(Glib::ustring value) {
  _ip = value;
}

void Host::set__description(Glib::ustring value) {
  _description = value;
}

//debug operation
void Host::print_processes() {
	std::cout << "Host::print_processes() " << std::endl;
	std::map<int, Process>::iterator process_iterator;
	for(process_iterator = _task_list.begin(); process_iterator != _task_list.end(); ++process_iterator ) {
		std::string sync("");
		if  ( (*process_iterator).second.get__synchronized() ){
			sync = "true";
		} else {
			sync = "false";
		}
		std::cout << (*process_iterator).first << " => [" 
					<< (*process_iterator).second.get__name() << ":"
					<< (*process_iterator).second.get__PPID() << ":"
					<< sync 
					<< "]" << std::endl;
	}
}
