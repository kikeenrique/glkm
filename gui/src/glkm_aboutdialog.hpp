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

#ifndef GLKM_ABOUTDIALOG_H
#define GLKM_ABOUTDIALOG_H

#include <config.h>
#include <gtkmm/aboutdialog.h>
#include <libglademm.h>

class GlkmAboutDialog : public Gtk::AboutDialog
{
public:

	GlkmAboutDialog(BaseObjectType* cobject, const Glib::RefPtr<Gnome::Glade::Xml>& refGlade);
	virtual ~GlkmAboutDialog();

protected:
	//Signal handlers:
	virtual void on_button_quit(int response_id);
		
	Glib::RefPtr<Gnome::Glade::Xml> m_refGlademmXml;

	void on_activate_link_url(AboutDialog& about_dialog, const Glib::ustring& link);
	void on_activate_email_url(AboutDialog& about_dialog, const Glib::ustring& email);
};

#endif //GLKM_ABOUTDIALOG_H
