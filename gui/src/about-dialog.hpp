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

#ifndef _ABOUTDIALOG_HPP
#define _ABOUTDIALOG_HPP

#include <gtkmm/aboutdialog.h>
#include <glibmm/ustring.h>
#include "utils.hpp"

class AboutDialog : public Gtk::AboutDialog {
  public:
	AboutDialog(BaseObjectType * cobject, const RefPtrGladeXml & refGlade);
	virtual ~AboutDialog();

  protected:
	RefPtrGladeXml _refGlademmXml;
	//Signal handlers:
	void on_signal_response(int response_id);
		
	void on_activate_link_url(Gtk::AboutDialog& about_dialog, const Glib::ustring& link);
	void on_activate_email_url(Gtk::AboutDialog& about_dialog, const Glib::ustring& email);
};

#endif //_ABOUTDIALOG_HPP
