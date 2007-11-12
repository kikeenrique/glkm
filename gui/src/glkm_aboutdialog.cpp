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

#include "glkm_aboutdialog.hpp"
#include <gtkmm/dialog.h>
#include <iostream>

#ifdef HAVE_LIBGNOME
#include <libgnome/gnome-url.h>
#endif // HAVE_LIBGNOME

#ifdef DEBUG
#include "debug.hpp"
#endif // DEBUG


GlkmAboutDialog::GlkmAboutDialog(BaseObjectType* cobject, const Glib::RefPtr<Gnome::Glade::Xml>& refGlade)
	:Gtk::AboutDialog(cobject),
	m_refGlademmXml(refGlade)
{
	//Actioning close button doesn't work by itself, needs a gobernant signal to http://mail.gnome.org/archives/gtkmm-list/2007-January/msg00305.html
	signal_response().connect( sigc::mem_fun(*this, &GlkmAboutDialog::on_button_quit) ); 

	set_url_hook(sigc::mem_fun(*this, &GlkmAboutDialog::on_activate_link_url) );
	set_email_hook(sigc::mem_fun(*this, &GlkmAboutDialog::on_activate_email_url) );
}

GlkmAboutDialog::~GlkmAboutDialog()
{
	//Null
}

void GlkmAboutDialog::on_button_quit(int response_id)
{
	switch(response_id) {
//		case Gtk::RESPONSE_DELETE_EVENT  :
		case Gtk::RESPONSE_CANCEL : 
			#ifdef DEBUG
			std::cout << "DELETE_EVENT/CANCEL"  << std::endl;
			#endif // DEBUG
			hide();
			break;
		default:
			;
			#ifdef DEBUG
			std::cout << "unattended event" << response_id << std::endl;
			#endif // DEBUG
	} 
}

void GlkmAboutDialog::on_activate_link_url(AboutDialog& about_dialog, const Glib::ustring& link)
{
#ifdef HAVE_LIBGNOME
	GError *error = NULL;
#endif // HAVE_LIBGNOME

#ifdef DEBUG
	std::cout << "link url" << std::endl;
#endif // DEBUG

#ifdef HAVE_LIBGNOME
	if (gnome_url_show(link.c_str(), &error)){
			std::cout << "good" << std::endl;			
	}else{
			std::cout << "wrong" << std::endl;			
	}
	
	if (error != NULL){
		g_warning (error->message);
		g_error_free (error);
	}
#endif // HAVE_LIBGNOME
}

void GlkmAboutDialog::on_activate_email_url(AboutDialog& about_dialog, const Glib::ustring& email)
{
#ifdef DEBUG
	Glib::ustring link="mailto:"+email;
#endif // DEBUG
#ifdef HAVE_LIBGNOME
	GError *error = NULL;
#endif // HAVE_LIBGNOME

#ifdef DEBUG
	std::cout << "email url" << std::endl;
#endif // DEBUG

#ifdef HAVE_LIBGNOME
	if (gnome_url_show(link.c_str(), &error)){
			std::cout << "good" << std::endl;			
	}else{
			std::cout << "wrong" << std::endl;			
	}
	
	if (error != NULL){
		g_warning (error->message);
		g_error_free (error);
	}
#endif // HAVE_LIBGNOME
}
