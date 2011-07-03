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
#include "main-window.hpp"
#include "hosts.hpp"
#include "notebook-hosts.hpp"
#include "icon-view-hosts.hpp"
#include "notebook-page-host.hpp"
#include "host.hpp"
#include "host-select-dialog.hpp"
#include "status-bar.hpp"
#include "tree-view-host.hpp"

#include "config.h"
#include "debug.hpp"

Controller & Controller::instance() {
    return singleton;
}

/*
 *
 */
void Controller::action_host_selected() {
    // Get host user selected
    IconViewHosts * _pIconViewHosts_local = _pMainWindow->_pHostSelectDialog->_pIconViewHosts;
    ListTreeModelPath selected = _pIconViewHosts_local->get_selected_items();

    if (!selected.empty()) {
        const Gtk::TreeModel::Path& path = *selected.begin();
        Gtk::TreeModel::iterator iter = _pIconViewHosts_local->_refPtrListStore->get_iter(path);
        Gtk::TreeModel::Row row = *iter;
        //Get column col_XX value
        const Glib::ustring hostname = row[_pIconViewHosts_local->_ModelColumns.col_hostname];
        const Glib::ustring ip = row[_pIconViewHosts_local->_ModelColumns.col_ip];
        const Glib::ustring description = row[_pIconViewHosts_local->_ModelColumns.col_description];

        PRINTD("Selected: hostname=" + hostname);
        _pHosts->create_host(hostname, ip, description);
    }

}


/*
 *
 */
void Controller::action_host_connect() {
    NotebookHosts * _pNotebookHosts_local = _pMainWindow->_pNotebookHosts;

    int current_page_number;
    current_page_number = _pNotebookHosts_local->get_current_page();

    NotebookPageHost * current_page;
//  current_page = static_cast<NotebookPageHost *> (current_page_number->get_child());
    current_page = static_cast<NotebookPageHost *> (_pNotebookHosts_local->get_nth_page(current_page_number));
    Host * present_host;
    present_host = current_page->get_my_Host();
    PRINTD("Controller:: connect=" + present_host->get__hostname());

    StatusBar * _pStatusBar_local = _pMainWindow->_pStatusBar;
    _pStatusBar_local->push_item("connecting...");
    present_host->connect();
    _pStatusBar_local->push_item("connected !");
    present_host->get_all_processes();
}


/*
 *
 */
void Controller::action_host_synchronize() {
    NotebookHosts * _pNotebookHosts_local = _pMainWindow->_pNotebookHosts;
    int current_page_number;
    current_page_number = _pNotebookHosts_local->get_current_page();

    NotebookPageHost * current_page;
//  current_page = static_cast<NotebookPageHost *> (current_page_number->get_child());
    current_page = static_cast<NotebookPageHost *> (_pNotebookHosts_local->get_nth_page(current_page_number));
    Host * present_host;
    present_host = current_page->get_my_Host();
    PRINTD("Controller:: synchronize=" + present_host->get__hostname());
    present_host->get_all_processes();
}


/*
 *
 */
void Controller::action_processes_selected() {
    NotebookHosts * _pNotebookHosts_local = _pMainWindow->_pNotebookHosts;
    int current_page_number;
    current_page_number = _pNotebookHosts_local->get_current_page();
    NotebookPageHost * current_page;
//  current_page = static_cast<NotebookPageHost *> (current_page_number->get_child());
    current_page = static_cast<NotebookPageHost *> (_pNotebookHosts_local->get_nth_page(current_page_number));

    TreeViewHost * _pTreeViewHost_local = current_page->get__pTreeViewHost();
    RefPtrTreeSelection refptr_treeselection = _pTreeViewHost_local->get_selection();

    PRINTD("Controller:: get selected row");
    /*  Gtk::TreeSelection::ListHandle_Path selected = refptr_treeselection->get_selected_rows();

        Gtk::TreeSelection::ListHandle_Path::iterator selected_iterator = selected.begin();

        Host * present_host;
        present_host = current_page->get_my_Host();

        for (;selected_iterator != selected.end(); selected_iterator++){
            Gtk::TreeStore::Path path = *selected_iterator;
            Gtk::TreeStore::iterator iter = _pTreeViewHost_local->get_model()->get_iter(path);
            if(iter) {
                Gtk::TreeStore::Row row = *iter;
                std::cout << "Row activated: PID=" << row[_pTreeViewHost_local->_ModelColumns.col_PID] << ", Name="
                << row[_pTreeViewHost_local->_ModelColumns.col_name] << std::endl;
            }
    */
    Gtk::TreeModel::iterator selected_iterator = refptr_treeselection->get_selected();

    Host * present_host;
    present_host = current_page->get_my_Host();

    if (selected_iterator) {
        Gtk::TreeModel::Row row = *selected_iterator;
        //Do something with the row.
        int PID = row[_pTreeViewHost_local->_ModelColumns.col_PID];
        //ustring name = row[_pTreeViewHost_local->_ModelColumns.col_name];
        std::cout << "Row activated: PID=" << PID << ", Name="
                  << row[_pTreeViewHost_local->_ModelColumns.col_name] << std::endl;

        Process process;

        present_host->get_process(PID, process);
        present_host->signal_process_monitor_begin.emit(&process);
    }

//      Process process;
//      present_host->get_process(row[_pTreeViewHost_local->_ModelColumns.col_PID], &process);
//      process.signal_process_monitor_begin.emit();

}


/*
 *
 */
void Controller::init_host_added() {
    NotebookHosts * _pNotebookHosts_local = _pMainWindow->_pNotebookHosts;
    //_pHost exists because its created in Controller constructor
    _pHosts->signal_host_added.connect(sigc::mem_fun(*_pNotebookHosts_local,
                                       &NotebookHosts::on_host_added) );
}


void Controller::set__pMainWindow(MainWindow * value) {
    _pMainWindow = value;
}


Controller Controller::singleton;

Controller::Controller() {
    if (_pHosts==NULL) {
        _pHosts = new Hosts();
    }
}

Controller::Controller(const Controller & source) {
}

Controller & Controller::operator=(const Controller & source) {
}

