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


#include <iostream>
#include <sstream>

#include "config.h"
#include "status-bar.hpp"

#include "debug.hpp"

StatusBar::StatusBar(BaseObjectType * cobject, const RefPtrGladeXml & refGlade):
	Gtk::Statusbar(cobject),
	_refGlademmXml(refGlade),
	_count(1)
{
	_context_id = get_context_id("Statusbar example");
}

StatusBar::~StatusBar()
{
	//Null
}

void StatusBar::push_item(const Glib::ustring& text, unsigned int context_id)
{
//TODO	g_snprintf(text, 20, "Item %d", m_count++);
	push(text, context_id);
}

void StatusBar::push_item(unsigned int context_id)
{
	std::stringstream converter;

	converter << "Item " << _count++;
	Glib::ustring buff(converter.str());
//	g_snprintf(buff, 20, "Item %d", m_count++);
	push(buff, context_id);
}

void StatusBar::pop_item(unsigned int context_id)
{ 
	pop(context_id);
}
