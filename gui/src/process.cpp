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

#include "debug.hpp"


Process::Process()
{
	#ifdef DEBUG
	//pDebug->debug_print("Constructor procces");
	#endif // DEBUG
}

Process::~Process()
{
	//Null
}

void Process::set__PPID(int value) {
  _PPID = value;
	#ifdef DEBUG
//	pDebug->debug_print("PPID:" + value);
	#endif // DEBUG	
}
