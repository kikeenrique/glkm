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

#include "host-select-dialog.hpp"
#include "icon-view-hosts.hpp"
#include "controller.hpp"

#include "config.h"
#include "debug.hpp"

HostSelectDialog::HostSelectDialog(BaseObjectType * cobject, const RefPtrGladeXml & refGlade):
	Gtk::Dialog(cobject),
	_refGlademmXml(refGlade)
{
	/* Actioning close button doesn't work by itself, needs a gobernant signal 
	 to http://mail.gnome.org/archives/gtkmm-list/2007-January/msg00305.html */
	signal_response().connect( sigc::mem_fun(*this, &HostSelectDialog::on_signal_response));

	//Icon View Hosts list
	_refGlademmXml->get_widget_derived("host_select_dialog-iconview", _pIconViewHosts);
	if (_pIconViewHosts){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}

 	//Buttons Accept and Cancel
	_refGlademmXml->get_widget("host_select_dialog-button_accept", _pButtonAccept);
	if (_pButtonAccept){
		_pButtonAccept->signal_clicked().connect( sigc::mem_fun(*this,	
																   &HostSelectDialog::on_clicked_button_accept) );
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}	
	_refGlademmXml->get_widget("host_select_dialog-button_cancel", _pButtonCancel);
	if (_pButtonCancel){
		_pButtonCancel->signal_clicked().connect( sigc::mem_fun(*this,	
																   &HostSelectDialog::on_clicked_button_cancel) );
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}

	//Set pointer in Controller that permits access to IconViewHosts 
	Controller& c = Controller::instance();
	c.set__pIconViewHosts(_pIconViewHosts);
}

HostSelectDialog::~HostSelectDialog() {
		PRINTD("~HostSelectDialog");
}

void HostSelectDialog::on_signal_response(int response_id)
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
			PRINTD("unattended event");
			PRINTD(response_id);
			;
	}
}

void HostSelectDialog::on_clicked_button_accept() {
	PRINTD("on_clicked_button_accept");

	//Tell controller that a new host could have been selected
	Controller& c = Controller::instance();
	c.action_host_selected();

	hide();
}

void HostSelectDialog::on_clicked_button_cancel() {
	PRINTD("on_clicked_button_cancel");
	hide();
}
