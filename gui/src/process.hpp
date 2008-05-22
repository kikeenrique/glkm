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

#ifndef _PROCCES_HPP
#define _PROCCES_HPP

#include <vector>
#include <glibmm/ustring.h>

#include "config.h"

class File;

class Procces
{
  public:
	Procces();
	virtual ~Process();
	inline const int get__PID() const;
	void set__PPID(int value);
	inline const Glib::ustring get__name() const;

  protected:
	int _PID;
	int _PPID;
	Glib::ustring _name;
	
	vector<File *> files_opened;
	
	
};

inline const int Process::get__PID() const {
  return _PID;
}

inline const Glib::ustring Process::get__name() const {
  return _name;
}

#endif // _PROCCES_HPP
