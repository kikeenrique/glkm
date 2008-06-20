/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * gui
 * Copyright (C) Enrique García Álvarez 2007 <kike+glkm@eldemonionegro.com>
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

#include "process.hpp"
#include "file.hpp"

#include "config.h"
#include "debug.hpp"


Process::Process(){
	_PID = 1;
	_PPID = 1;
	_name = "";
}

Process::~Process(){
	//Null
}

Process::Process(const Process & source) :
	_PID(source._PID),
	_PPID(source._PPID),
	_name(source._name)
{
	//TODO
	//std::vector<File *> files_opened;
}

Process & Process::operator=(const Process & source) {
	_PID = source._PID;
	_PPID = source._PPID;
	_name = source._name;	
	//TODO
	//	std::vector<File *> files_opened;
	return *this;	
}

void Process::set__PID(int value) {
  _PID = value;
}

void Process::set__PPID(int value) {
  _PPID = value;
}

void Process::set__name(Glib::ustring value) {
	_name = value;
/*	if (_name.validate()){
		PRINTD ("Process() validated ");
	} else {
		PRINTD ("Process() validated NOT ");
	}*/
}
