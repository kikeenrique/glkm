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


#include <iostream>

#include "config.h"
#ifdef HAVE_LIBGNOME
#include <libgnome/gnome-url.h>
#endif // HAVE_LIBGNOME

#include "about-dialog.hpp"
#include "debug.hpp"

AboutDialog::AboutDialog(BaseObjectType* cobject, const Glib::RefPtr<Gnome::Glade::Xml>& refGlade)
	:Gtk::AboutDialog(cobject),
	_refGlademmXml(refGlade)
{
	/* Actioning close button doesn't work by itself, needs a gobernant signal 
	 to http://mail.gnome.org/archives/gtkmm-list/2007-January/msg00305.html */
	signal_response().connect( sigc::mem_fun(*this, &AboutDialog::on_signal_response)); 

	set_url_hook(sigc::mem_fun(*this, &AboutDialog::on_activate_link_url));
	set_email_hook(sigc::mem_fun(*this, &AboutDialog::on_activate_email_url));
}

AboutDialog::~AboutDialog()
{
	PRINTD("~AboutDialog");
}

void AboutDialog::on_signal_response(int response_id)
{
	switch(response_id) {
		case Gtk::RESPONSE_NONE :
			PRINTD("RESPONSE_NONE");
			hide();
			break;
		case Gtk::RESPONSE_REJECT :
			PRINTD("RESPONSE_REJECT");
			hide();
			break;
		case Gtk::RESPONSE_ACCEPT :
			PRINTD("RESPONSE_ACCEPT");
			hide();
			break;
		case Gtk::RESPONSE_DELETE_EVENT :
			PRINTD("RESPONSE_DELETE_EVENT");
			hide();
			break;
		case Gtk::RESPONSE_OK :
			PRINTD("RESPONSE_OK");
			hide();
			break;
		case Gtk::RESPONSE_CANCEL :
			PRINTD("RESPONSE_CANCEL");
			hide();
			break;
		case Gtk::RESPONSE_CLOSE :
			PRINTD("RESPONSE_CLOSE");
			hide();
			break;
		case Gtk::RESPONSE_YES :
			PRINTD("RESPONSE_YES");
			hide();
			break;
		case Gtk::RESPONSE_NO :
			PRINTD("RESPONSE_NO");
			hide();
			break;
		case Gtk::RESPONSE_APPLY :
			PRINTD("RESPONSE_APPLY");
			hide();
			break;
		case Gtk::RESPONSE_HELP :
			PRINTD("RESPONSE_HELP");
			hide();
			break;
		default:
			PRINTD("unattended event" + response_id);
			;
	}
}

void AboutDialog::on_activate_link_url(Gtk::AboutDialog& about_dialog, const Glib::ustring& link)
{
	PRINTD("on_activate_link_url");
#ifdef HAVE_LIBGNOME
	GError *error = NULL;

    if (gnome_url_show(link.c_str(), &error)){
		PRINTD("activate_link ok");
	}else{
		PRINTD("activate_link BAD");
	}

	if (error != NULL){
		g_warning (error->message);
		g_error_free (error);
	}
#endif // HAVE_LIBGNOME
}

void AboutDialog::on_activate_email_url(Gtk::AboutDialog& about_dialog, const Glib::ustring& email)
{

	Glib::ustring link="mailto:"+email;

	PRINTD("on_activate_email_url");
#ifdef HAVE_LIBGNOME
	GError *error = NULL;

    if (gnome_url_show(link.c_str(), &error)){
		PRINTD("activate_email ok");
	}else{
		PRINTD("activate_email BAD");
	}	
	if (error != NULL){
		g_warning (error->message);
		g_error_free (error);
	}
#endif // HAVE_LIBGNOME

}
