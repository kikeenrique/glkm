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

#include "controller.hpp"
#include "hosts.hpp"
#include "main-window.hpp"
#include "icon-view-hosts.hpp"

#include "config.h"
#include "debug.hpp"

void Controller::action_host_selected() {
	// Get host user selected
	ListTreeModelPath selected = _pIconViewHosts->get_selected_items();
        
	if(!selected.empty()){
		const Gtk::TreeModel::Path& path = *selected.begin();
		Gtk::TreeModel::iterator iter = _pIconViewHosts->_refPtrListStore->get_iter(path);
		Gtk::TreeModel::Row row = *iter;
		//Get column col_XX value 
		const Glib::ustring hostname = row[_pIconViewHosts->_ModelColumns.col_hostname];
		const Glib::ustring ip = row[_pIconViewHosts->_ModelColumns.col_ip];
		const Glib::ustring description = row[_pIconViewHosts->_ModelColumns.col_description];

		PRINTD("Selected: hostname=" + hostname);

		_pHosts->create_host(hostname, ip, description);
	}

}

Controller & Controller::instance(){
	return singleton;
}

void Controller::update() {
}

void Controller::set__pHosts(Hosts * value) {
  _pHosts = value;
}

void Controller::set__pIconViewHosts(IconViewHosts * value) {
  _pIconViewHosts = value;
}

Controller Controller::singleton;

Controller::Controller() {
	_pHosts = new Hosts();
}

Controller::Controller(const Controller & source) {
}

Controller & Controller::operator=(const Controller & source) {
}
