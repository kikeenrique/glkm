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

#ifndef _DEBUG_HPP
#define _DEBUG_HPP

#include <gtkmm/textview.h>
#include <glibmm/ustring.h>

#include <iostream>

#include "utils.hpp"
#include "config.h"

/*
	PRINT_EXP(A)
	Macro for printing the values of variables during debugging
	Example: 
			int a = 1, b = 2, c = 3;
			P(a); P(b); P(c);
			P(a + b);
			P((c - a)/b);
*/
#define PRINT_EXP(A) std::cout << #A << ": " << (A) << std::endl;

/*
	PRINTD(A)
	Macro for printing text messages to a notebook page (into main window).
	A should be of type char * or Glib::ustring.
	When using two or more const char * you should use std::string
	Example:
		* One const char *:
			PRINTD("ID=" + row[id]);
	
		* Two or more const char *:
			PRINTD("ID=" + row[id] 
			       + std::string(", Name=") + row[name] );

*/
#ifdef DEBUG
#define PRINTD(A) {					\
			extern TextViewDebug*	pDebug; \
			pDebug->debug_print(A);		\
		}
#else
#define PRINTD(A) {}
#endif // DEBUG	

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
 *
 */
class TextViewDebug : public Gtk::TextView {
  public:
	TextViewDebug(BaseObjectType * cobject, const RefPtrGladeXml & refGlade);
	virtual ~TextViewDebug();
	void debug_print(const Glib::ustring& text);
	void debug_print(const char* text);
	void debug_print(const int & number);

  protected:
	RefPtrGladeXml _refPtrGlademmXml;

	//Text model buffer:
	virtual void fill_buffer();  
	Glib::RefPtr<Gtk::TextBuffer> _refPtrTextBuffer;
	Gtk::TextBuffer::iterator _position;
	
	Glib::ustring get_timestamp();
};

#endif //_DEBUG_HPP

