/*
 * gui
 * Copyright (C) Enrique Garcia Alvarez 2007-2008 <kike+glkm@eldemonionegro.com>
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

#ifndef _UTILS_HPP
#define _UTILS_HPP

#include <vector>
#include <map>
#include <string>
#include <list>

#include <gtkmm/textbuffer.h>
#include <gtkmm/treeselection.h>
#include <gtkmm/treestore.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treemodel.h>

#include <glibmm/refptr.h>
#include <glibmm/ustring.h>

#include <gdkmm/pixbuf.h>

#include <libglademm/xml.h>

#include <dbusmm/types.h>


typedef std::vector<DBus::String> VectorString;
typedef std::map<DBus::String, DBus::Variant> DictVariable;
typedef Glib::RefPtr<Gnome::Glade::Xml> RefPtrGladeXml;
typedef Glib::RefPtr<Gtk::TextBuffer> RefPtrTextBuffer;
typedef Glib::RefPtr<Gtk::TreeSelection> RefPtrTreeSelection;
typedef Glib::RefPtr<Gtk::TreeStore> RefPtrTreeStore;
typedef Gtk::TreeModelColumn<int> TreeModelColumnInt;
typedef Gtk::TreeModelColumn<Glib::ustring> TreeModelColumnUstring;
typedef Glib::RefPtr<Gtk::ListStore> RefPtrListStore;
typedef Gtk::TreeModelColumn<std::string> TreeModelColumnString;
typedef Glib::RefPtr<Gdk::Pixbuf> RefPtrPixbuf;
typedef Gtk::TreeModelColumn<RefPtrPixbuf> TreeModelColumnRefPtrPixbuf;
typedef std::list<Gtk::TreeModel::Path> ListTreeModelPath;

#endif // _UTILS_HPP
