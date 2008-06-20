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
	_hal_controller(source._hal_controller),
	_filesystems(source._filesystems)
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
		_hal_controller = new HalController ();
	} else {
		PRINTD ("Host:: already connected " + _hostname);
	}
}

void Host::get_all_processes() {
	bool result;
	result = _hal_controller->get_all_processes(*this);
}

bool Host::get_process(int PID, Process & process){
	bool ret=true;

	//REWORK this creates task_list[PID] even if process with PID does not exists
//	process=task_list[PID];
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
