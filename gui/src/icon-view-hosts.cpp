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

#include "icon-view-hosts.hpp"

#include <config.h>
#include "debug.hpp"

IconViewHosts::IconViewHosts(BaseObjectType * cobject, const RefPtrGladeXml & refGlade):
	Gtk::IconView(cobject),
	_refPtrGlademmXml(refGlade)
{
  // Create the Tree model:
  _refPtrListStore = Gtk::ListStore::create(_ModelColumns);
  _refPtrListStore->set_sort_column( _ModelColumns.col_description, Gtk::SORT_ASCENDING );

  set_model(_refPtrListStore);
	
  set_markup_column(_ModelColumns.col_description);
  set_pixbuf_column(_ModelColumns.col_pixbuf);
	
  signal_item_activated().connect(sigc::mem_fun(*this,
																			&IconViewHosts::on_item_activated) );
  signal_selection_changed().connect(sigc::mem_fun(*this,
																			&IconViewHosts::on_selection_changed) );
/*
  IconEntry entries[] =
  {
    IconEntry("mozilla-firefox.png", "<b>Mozilla Firefox</b> Logo"),
    IconEntry("xmms.xpm", "<b>XMMS</b> Logo"),
    IconEntry("gnome-dice-1.svg", "<b>Gnome Dice 1</b> Logo"),
    IconEntry("gnome-dice-2.svg", "<b>Gnome Dice 2</b> Logo"),
    IconEntry("gnome-dice-3.svg", "<b>Gnome Dice 3</b> Logo"),
    IconEntry("gnome-dice-4.svg", "<b>Gnome Dice 4</b> Logo"),
    IconEntry("gnome-dice-5.svg", "<b>Gnome Dice 5</b> Logo"),
    IconEntry("gnome-dice-6.svg", "<b>Gnome Dice 6</b> Logo")
  };
*/

	// Fill the TreeView's model
/*
  const int count = sizeof( entries ) / sizeof( IconEntry );
  for( int idx = 0; idx < count; ++idx )
  {
    add_entry( entries[idx].m_filename, entries[idx].m_description );
  }
*/
  show_all_children();

}

IconViewHosts::~IconViewHosts() {
	PRINTD("~IconViewHosts");
}

void IconViewHosts::on_item_activated(const Gtk::TreeModel::Path & path) {
	Gtk::TreeModel::iterator iter = _refPtrListStore->get_iter(path);
	Gtk::TreeModel::Row row = *iter;

	const std::string filename = row[_ModelColumns.col_filename];
	const Glib::ustring description = row[_ModelColumns.col_description];

	PRINTD("Item activated: filename= " + filename);
	PRINTD("description= " + description);

}

void IconViewHosts::on_selection_changed() {
	typedef std::list<Gtk::TreeModel::Path> type_list_paths;
	type_list_paths selected = get_selected_items();
	
	if(!selected.empty()){
		const Gtk::TreeModel::Path& path = *selected.begin();
		Gtk::TreeModel::iterator iter = _refPtrListStore->get_iter(path);
		Gtk::TreeModel::Row row = *iter;
		const std::string filename = row[_ModelColumns.col_filename];
		const Glib::ustring description = row[_ModelColumns.col_description];

		PRINTD("Selection Changed to: filename=" + filename);
		PRINTD("description= " + description);
	}
}

/*
void ExampleWindow::add_entry(const std::string& filename,
        const Glib::ustring& description )
{
  Gtk::TreeModel::Row row = *(_refPtrListStore->append());
  row[_ModelColumns.col_filename] = filename;
  row[_ModelColumns.col_description] = description;

  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  row[_ModelColumns.col_pixbuf] = Gdk::Pixbuf::create_from_file(filename);
  #else
  std::auto_ptr<Glib::Error> error;
  row[_ModelColumns.col_pixbuf] = Gdk::Pixbuf::create_from_file(filename, error);
  #endif //GLIBMM_EXCEPTIONS_ENABLED
}
*/
