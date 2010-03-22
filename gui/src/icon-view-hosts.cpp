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

#include <string>

#include "icon-view-hosts.hpp"

#include "config.h"
#include "debug.hpp"

IconViewHosts::IconViewHosts(BaseObjectType * cobject, const RefPtrBuilder & refBuilder):
	Gtk::IconView(cobject),
	_refPtrBuilder(refBuilder)
{
	_refPtrBuilder->get_widget_derived("host_select_dialog-textview", _TextViewHosts);
	if (_TextViewHosts){
	} else{
		std::cerr << "** ERROR ** Maybe an error loading glade file?" << std::endl;
	}

	signal_item_activated().connect(sigc::mem_fun(*this,
												  &IconViewHosts::on_item_activated) );
	signal_selection_changed().connect(sigc::mem_fun(*this,
												     &IconViewHosts::on_selection_changed) );

	_refPtrListStore = Gtk::ListStore::create(_ModelColumns);
	_refPtrListStore->set_sort_column( _ModelColumns.col_ip, Gtk::SORT_ASCENDING );

	set_model(_refPtrListStore);
	set_markup_column(_ModelColumns.col_hostname);
	set_pixbuf_column(_ModelColumns.col_pixbuf);
	
	//TODO
	//This is just a test code
	// Add our hosts to the TreeView's model
	add_entry("localhost", "127.0.0.1", "Our current host");
	add_entry("localhost", "127.0.0.1", "A remote host (virtualbox host) need var environment DBUS_SYSTEM_BUS_ADDRESS");
	add_entry("garfield", "192.168.0.5", "A host in our net");
	add_entry("eldemonionegro.com", "89.128.19.104", "A remote host. Don't even try it by now");

	show_all_children();
}

IconViewHosts::~IconViewHosts() {
	PRINTD("~IconViewHosts");
}

void IconViewHosts::on_item_activated(const Gtk::TreeModel::Path & path) {
	Gtk::TreeModel::iterator iter = _refPtrListStore->get_iter(path);
	Gtk::TreeModel::Row row = *iter;

	//Show info to user
	const Glib::ustring hostname = row[_ModelColumns.col_hostname];
	show_entry (hostname,
			    row[_ModelColumns.col_ip],
			    row[_ModelColumns.col_description]);	
	PRINTD("Item Activated:" + hostname);
}

void IconViewHosts::on_selection_changed() {
	typedef std::list<Gtk::TreeModel::Path> type_list_paths;
	type_list_paths selected = get_selected_items();
	
	if(!selected.empty()){
		const Gtk::TreeModel::Path& path = *selected.begin();
		Gtk::TreeModel::iterator iter = _refPtrListStore->get_iter(path);
		Gtk::TreeModel::Row row = *iter;
		//Show info to user
		//Get column col_XX value 
		const Glib::ustring hostname = row[_ModelColumns.col_hostname];
		show_entry (hostname,
				    row[_ModelColumns.col_ip],
				    row[_ModelColumns.col_description]);	
		PRINTD("Selection Changed to: hostname=" + hostname);
	}
}

IconViewHosts::TextViewHosts::TextViewHosts(BaseObjectType * cobject, const RefPtrBuilder & refBuilder)
	:Gtk::TextView(cobject),
	 _refPtrBuilder(refBuilder)
{
	_refPtrTextBuffer = get_buffer();
	show_all_children();
}

IconViewHosts::TextViewHosts::~TextViewHosts() {
	//Null
}

void IconViewHosts::TextViewHosts::show_hostname(const Glib::ustring & hostname) {
	_refPtrTextBuffer->insert_at_cursor("Hostname: " + hostname + "\n");
}

void IconViewHosts::TextViewHosts::show_ip(const Glib::ustring & ip) {
	_refPtrTextBuffer->insert_at_cursor("IP: " + ip + "\n");
}

void IconViewHosts::TextViewHosts::show_description(const Glib::ustring & description) {
	_refPtrTextBuffer->insert_at_cursor("Description: " + description + "\n");
}

void IconViewHosts::TextViewHosts::reset() {
	_refPtrTextBuffer->set_text("");
}

void IconViewHosts::add_entry(const Glib::ustring & hostname, 
							  const Glib::ustring & ip, 
							  const Glib::ustring & description) {						  
	Gtk::TreeModel::Row row = *(_refPtrListStore->append());
	row[_ModelColumns.col_hostname] = hostname;
	row[_ModelColumns.col_ip] = ip;
	row[_ModelColumns.col_description] = description;

//TODO
//Need to look for code that autolocates default icons path and it only needs 
//icon name
/*
PACKAGE_PIXMAPS_DIR"/"GLKM_PIXMAP_LOCALHOST
	const std::string FILENAME="search";
#ifdef GLIBMM_EXCEPTIONS_ENABLED
	try
	{
		row[_ModelColumns.col_pixbuf] = Gdk::Pixbuf::create_from_file(FILENAME);
	}
	catch(const Glib::Error& exception)
    {
		std::cerr << exception.what() << std::endl;
//		throw;
	}	
#else
	std::auto_ptr<Glib::Error> error;
	row[_ModelColumns.col_pixbuf] = Gdk::Pixbuf::create_from_file(FILENAME, error);
	if (error.get())
	{
		std::cerr << error->what() << std::endl;
		return 1;
	}
#endif //GLIBMM_EXCEPTIONS_ENABLED
*/
}

void IconViewHosts::show_entry(const Glib::ustring & hostname, 
							  const Glib::ustring & ip, 
							  const Glib::ustring & description) {

	//Show info to user
	_TextViewHosts->reset ();
	_TextViewHosts->show_hostname (hostname);
	_TextViewHosts->show_ip (ip);
	_TextViewHosts->show_description (description);
}
