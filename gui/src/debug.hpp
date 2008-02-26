/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * debug.hpp
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
 * 	The Free Software Foundation, Inc.,
 * 	51 Franklin Street, Fifth Floor
 * 	Boston, MA  02110-1301, USA.
 */

#ifndef GLKM_DEBUG_HPP
#define GLKM_DEBUG_HPP

#include <config.h>
#include <gtkmm/textview.h>
#include <gtkmm/textbuffer.h>
#include <libglademm/xml.h>

#include <iostream>

/*
	PRINT(A)
	Macro for printing the values of variables during debugging
	Example: 
			int a = 1, b = 2, c = 3;
			P(a); P(b); P(c);
			P(a + b);
			P((c - a)/b);
*/
#define PRINT(A) std::cout << #A << ": " << (A) << std::endl;

/*
	std::assert();
	Debugging macro. When you use assert( ), you give it an argument that is an 
	expression you are “asserting to be true.” The preprocessor generates code that
	will test the assertion. If the assertion isn’t true, the program will stop after
	issuing an error message telling you what the assertion was and that it failed. 
	Example: 
			int i = 100;
			assert(i != 100); // Fails
*/
#include <assert.h>



/*
 * We are using a singleton
 */
class TextViewDebug : public Gtk::TextView
{
public:
	TextViewDebug(BaseObjectType* cobject, 
				  const Glib::RefPtr<Gnome::Glade::Xml>& refGlade);
	virtual ~TextViewDebug();
	void debug_print(const Glib::ustring& text);
	void debug_print(const char* text);
protected:

	Glib::RefPtr<Gnome::Glade::Xml> m_refGlademmXml;

	//Text model buffer:
	virtual void fill_buffers();  
	Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;

};



#endif //GLKM_DEBUG_HPP

