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

#ifndef _ICON_VIEW_HOSTS_HPP
#define _ICON_VIEW_HOSTS_HPP

#include <gtkmm/iconview.h>
#include "utils.hpp"

class IconViewHosts : public Gtk::IconView {
  public:
	IconViewHosts(BaseObjectType * cobject, const RefPtrGladeXml & refGlade);

	virtual ~IconViewHosts();
  protected:
	virtual void on_item_activated(const Gtk::TreeModel::Path& path);
	virtual void on_selection_changed();
	void add_entry(const std::string& filename, const Glib::ustring& description);

	// Tree model columns:
	//
	class ModelColumns : public Gtk::TreeModel::ColumnRecord {
	  public:
		ModelColumns(){
			add(_col_filename);
			add(_col_description);
			add(_col_pixbuf);
		}
		Gtk::TreeModelColumn<std::string> _col_filename;
		Gtk::TreeModelColumn<Glib::ustring>  _col_description;
		Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > _col_pixbuf;
	};

	ModelColumns _ModelColumns;

	Gtk::IconView _IconView;
	Glib::RefPtr<Gtk::ListStore> _refPtrListStore;

	RefPtrGladeXml _refGlademmXml;
};

#endif // _ICON_VIEW_HOSTS_HPP
