/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * glkm_aboutdialog.h
 * Copyright (C) Enrique García Álvarez 2007 <kike@eldemonionegro.com>
 * 
 * glkm_aboutdialog.h is free software.
 * 
 * You may redistribute it and/or modify it under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 * 
 * glkm_aboutdialog.h is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with main.cc.  If not, write to:
 * 	The Free Software Foundation, Inc.,
 * 	51 Franklin Street, Fifth Floor
 * 	Boston, MA  02110-1301, USA.
 */

#ifndef GLKM_ABOUTDIALOG_H
#define GLKM_ABOUTDIALOG_H

#include <gtkmm/aboutdialog.h>
#include <libglademm.h>

class GlkmAboutDialog : public Gtk::AboutDialog
{
public:

	GlkmAboutDialog(BaseObjectType* cobject, const Glib::RefPtr<Gnome::Glade::Xml>& refGlade);
	virtual ~GlkmAboutDialog();

protected:
	//Signal handlers:
	/*
	virtual void on_button_clicked();
	*/
	virtual void on_button_quit(int response_id);
		
	Glib::RefPtr<Gnome::Glade::Xml> m_refGlademmXml;

	void on_activate_link_url(AboutDialog& about_dialog, const Glib::ustring& link);
	void on_activate_email_url(AboutDialog& about_dialog, const Glib::ustring& email);
};

#endif //GLKM_ABOUTDIALOG_H
