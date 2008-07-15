/*
 * utils.hpp
 * Copyright (C) Enrique Garcia Alvarez 2007-2008 <kike+glkm@eldemonionegro.com>
 * 
 * utils.hpp is free software: you can redistribute it and/or modify it
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

#ifndef _UTILS_HPP
#define _UTILS_HPP

#include <glibmm/refptr.h>
#include <glibmm/main.h>

#include <giomm/fileinputstream.h>
#include <giomm/file.h>
#include <giomm/datainputstream.h>

#include <dbusmm/types.h>

#include <vector>

typedef std::vector<DBus::String> VectorString;
typedef Glib::RefPtr<Glib::MainLoop> MainLoopRefPtr;
typedef Glib::RefPtr<Gio::FileInputStream> RefPtrFileInputStream;
typedef Glib::RefPtr<Gio::File> RefPtrFile;
typedef Glib::RefPtr<Gio::DataInputStream> RefPtrDataInputStream;

#endif // _UTILS_HPP
