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

#include "glkm_statusbar.hpp"

#ifdef DEBUG
#include "debug.hpp"
#endif // DEBUG

#include <iostream>
#include <sstream>


GlkmStatusBar::GlkmStatusBar(BaseObjectType* cobject, const Glib::RefPtr<Gnome::Glade::Xml>& refGlade)
:	
	Gtk::Statusbar(cobject),
	m_refGlademmXml(refGlade),
	m_count(1)
{
	m_context_id = get_context_id("Statusbar example");
}

GlkmStatusBar::~GlkmStatusBar()
{
	//Null
}

void GlkmStatusBar::push_item(const Glib::ustring& text, unsigned int context_id)
{
//TODO	g_snprintf(text, 20, "Item %d", m_count++);
	push(text, context_id);
}

void GlkmStatusBar::push_item(unsigned int context_id)
{
	std::stringstream converter;

	converter << "Item " << m_count++;
	Glib::ustring buff(converter.str());
//	g_snprintf(buff, 20, "Item %d", m_count++);
	push(buff, context_id);
}

void GlkmStatusBar::pop_item(unsigned int context_id)
{ 
	pop(context_id);
}
