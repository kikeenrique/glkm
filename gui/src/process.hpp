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

#include <glibmm/ustring.h>

#include <vector>

class File;

class Process {
  public:
	Process();
	virtual ~Process();
	Process(const Process & source);
	Process & operator=(const Process & source);

	inline const int get__PID() const;
	void set__PID(int value);
	inline const int get__PPID() const;
	void set__PPID(int value);
	inline const Glib::ustring get__name() const;
	void set__name(Glib::ustring value);
	inline const bool get__synchronized() const;
	void set__synchronized(bool value);

  protected:
	int _PID;
	int _PPID;
	Glib::ustring _name;
	
	std::vector<File *> files_opened;
	
	bool _synchronized;
};
inline const int Process::get__PID() const {
  return _PID;
}

inline const int Process::get__PPID() const {
  return _PPID;
}

inline const Glib::ustring Process::get__name() const {
  return _name;
}
inline const bool Process::get__synchronized() const {
  return _synchronized;
}

#endif // _PROCCES_HPP
