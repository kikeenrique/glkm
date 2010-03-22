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
#include <gtkmm/treemodel.h>
#include <gtkmm/textview.h>

#include <glibmm/ustring.h>

#include "utils.hpp"

class IconViewHosts : public Gtk::IconView {
  public:
	IconViewHosts(BaseObjectType * cobject, const RefPtrBuilder & refBuilder);

	virtual ~IconViewHosts();
	
  protected:
  	RefPtrBuilder _refPtrBuilder;
	virtual void on_item_activated(const Gtk::TreeModel::Path & path);
	virtual void on_selection_changed();

	// Tree model columns:
	//
	class ModelColumns : public Gtk::TreeModel::ColumnRecord {
	  public:
		ModelColumns(){
			add(col_hostname);
			add(col_ip);	
			add(col_description);
			add(col_pixbuf);
		}
		TreeModelColumnUstring col_hostname;
		TreeModelColumnUstring col_ip;		
		TreeModelColumnUstring col_description;
//		TreeModelColumnString col_filename;		
		TreeModelColumnRefPtrPixbuf col_pixbuf;
	};



	class TextViewHosts : public Gtk::TextView {
	  public:
		TextViewHosts(BaseObjectType * cobject, const RefPtrBuilder & refBuilder);
		virtual ~TextViewHosts();
	  protected:
		RefPtrBuilder _refPtrBuilder;
		RefPtrTextBuffer _refPtrTextBuffer;
	  public:
		void show_hostname(const Glib::ustring & hostname);
		void show_ip(const Glib::ustring & ip);
		void show_description(const Glib::ustring & description);
		void reset();
    };
    
	TextViewHosts * _TextViewHosts;
  public:
	ModelColumns _ModelColumns;
	RefPtrListStore _refPtrListStore;
  private:
	void add_entry(const Glib::ustring & hostname, const Glib::ustring & ip, const Glib::ustring & description);
	void show_entry(const Glib::ustring & hostname, const Glib::ustring & ip, const Glib::ustring & description);	
};

#endif // _ICON_VIEW_HOSTS_HPP
