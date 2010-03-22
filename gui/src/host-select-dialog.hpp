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

#ifndef _HOST_SELECT_DIALOG_HPP
#define _HOST_SELECT_DIALOG_HPP

#include <gtkmm/dialog.h>
#include <gtkmm/button.h>
#include "utils.hpp"

class IconViewHosts;

class HostSelectDialog : public Gtk::Dialog {

  friend class Controller;

  public:
	HostSelectDialog(BaseObjectType * cobject, const RefPtrBuilder & refBuilder);
	virtual ~HostSelectDialog();
	
  protected:
	RefPtrBuilder _refPtrBuilder;

	void on_signal_response(int response_id);
	void on_clicked_button_accept();
	void on_clicked_button_cancel();

	IconViewHosts * _pIconViewHosts;

	Gtk::Button * _pButtonAccept;
	Gtk::Button * _pButtonCancel;

};

#endif // _HOST_SELECT_DIALOG_HPP
