/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * debug.h
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

#ifndef GLKM_DEBUG_H
#define GLKM_DEBUG_H

#include <iostream>

/*
	P(A)
	Macro for printing the values of variables during debugging
	Example: 
			int a = 1, b = 2, c = 3;
			P(a); P(b); P(c);
			P(a + b);
			P((c - a)/b);
*/
#define P(A) cout << #A << ": " << (A) << endl;

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

#endif //GLKM_DEBUG_H
