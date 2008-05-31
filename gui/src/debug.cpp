/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * debug.cpp
 * Copyright (C) Enrique García Álvarez 2007 <kike @ eldemonionegro.com>
 * 
 * debug.h is free software.
 * 
 * You may redistribute it and/or modify it under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 * 
 * debug.h is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with main.cc.  If not, write to:
 * 		The Free Software Foundation, Inc.,
 * 		51 Franklin Street, Fifth Floor
 *		Boston, MA  02110-1301, USA.
 */

#include "debug.hpp"
#include <sstream>

TextViewDebug::TextViewDebug (BaseObjectType* cobject, 
							  const Glib::RefPtr<Gnome::Glade::Xml>& refGlade)
	:Gtk::TextView(cobject),
	 _refPtrGlademmXml(refGlade)
{
	//Create the text buffer
	fill_buffer();
	
	show_all_children();
}

TextViewDebug::~TextViewDebug()
{
	//Null
}

void TextViewDebug::fill_buffer()
{
	_refPtrTextBuffer = get_buffer();
	_refPtrTextBuffer->set_text("BEGIN\n");
}

void TextViewDebug::debug_print(const Glib::ustring& text)
{
	_refPtrTextBuffer->insert_at_cursor(text+"\n");
}

void TextViewDebug::debug_print(const char* text)
{
	Glib::ustring tmp(text);
	_refPtrTextBuffer->insert_at_cursor(tmp+"\n");
}

void TextViewDebug::debug_print(const int & number)
{
	Glib::ustring tmp;
	std::stringstream out;
	out << number;
	tmp = out.str();

	_refPtrTextBuffer->insert_at_cursor(tmp+"\n");
}
