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

#ifndef _STATUS_BAR_HPP
#define _STATUS_BAR_HPP

#include <gtkmm/statusbar.h>
#include "utils.hpp"

class StatusBar: public Gtk::Statusbar {
  public:
	StatusBar(BaseObjectType * cobject, const RefPtrGladeXml & refGlade);
	virtual ~StatusBar();
	
	void push_item(const Glib::ustring & text, unsigned int context_id);
	void push_item(unsigned int context_id);
	void pop_item(unsigned int context_id);
	
  protected:
	RefPtrGladeXml _refGlademmXml;

	unsigned int	_context_id;
	unsigned int	_count;
};

#endif // _STATUS_BAR_HPP
