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

#ifndef _GLKM_STATUSBAR_HPP_
#define _GLKM_STATUSBAR_HPP_
#include <config.h>

//#include <gtkmm.h>
#include <libglademm/xml.h>
#include <gtkmm/statusbar.h>

class GlkmStatusBar: public Gtk::Statusbar 
{
public:
	GlkmStatusBar(BaseObjectType* cobject, const Glib::RefPtr<Gnome::Glade::Xml>& refGlade);
	void push_item(const Glib::ustring& text, unsigned int context_id);
	void push_item(unsigned int context_id);
	void pop_item(unsigned int context_id);
	virtual ~GlkmStatusBar();
	
protected:
	Glib::RefPtr<Gnome::Glade::Xml> m_refGlademmXml;		

	unsigned int	m_context_id;
	unsigned int	m_count;

private:

};

#endif // _GLKM_STATUSBAR_HPP_
