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

#include <iostream>
#include <sstream>

#include "hal-parser.hpp"
#include "host.hpp"
//#include "process.hpp"

#include "config.h"
#include "debug.hpp"


HalParser::HalParser() {
}

HalParser::~HalParser() {
}

/** 
 *  parse_add_processes:
 *  @hal_vs_processes:
 *  @host:
 *
 *  Returns:
 *
 *  Exceptions:
 *
 *  Example:
 *           Line format gets defined in kernel module with this format:
 *                              "%s:%d:%d\n",
 *                              task->comm,
 *                              task->pid,
 *                              task->parent->pid
 *
 */
void HalParser::parse_add_processes(VectorString & hal_task_list, Host & host) {

//	VectorString::iterator hal_task_list_it;
//	for(hal_task_list_it = hal_task_list.begin(); hal_task_list_it != hal_task_list.end(); ++hal_task_list_it) {
	/* 
	   We're going to loop processes reversed as hal_task_list goes from mayor 
	   to minor PID and we want to parented processes to be able to find its 
	   previously created parent
	 */
	VectorString::reverse_iterator hal_task_list_it;
	for(hal_task_list_it = hal_task_list.rbegin(); hal_task_list_it != hal_task_list.rend(); ++hal_task_list_it) {
		VectorString parsed_process;
		// TODO
		// We use iss and iss2 because working with just one doesn't work 
		// as expected. This shoul be looked up.
		std::istringstream iss;		
		std::istringstream iss2;
		Glib::ustring process_name;
		int PID;
	    int PPID;

		tokenize(*hal_task_list_it, ":", parsed_process);
		
		//When we get a line without all of our process parameters, skip it
		if (parsed_process.size() < 3) {
			std::cerr << "ERROR:: Bad formed hal line" << std::endl;
			PRINTD("HalParser ERROR:: Bad formed hal line ");
			continue;
		}

		// Get each process parameter into their proper variable type and look
		// for errors without broken program.
		// We use at() instead of [] becuase it provide us exceptions
		try {
			process_name = parsed_process.at(0);
			iss.str (parsed_process.at(1));
			iss >> PID;
			iss2.str (parsed_process.at(2));
			iss2 >> PPID;
		} catch (std::out_of_range exception){
			std::cerr << exception.what() << std::endl;
		}
			
		// Search for element with a value of PID and returns an iterator to it
		// if found. Otherwise it returns an iterator to map::end (the
		// element past the end of the container).
		std::map<int, Process>::iterator task_list_it;
		task_list_it = host._task_list.find(PID);

		if ( task_list_it == host._task_list.end() ) {
			//Process does not exists so we have to add it
			host._task_list[PID].set__PID(PID);
			host._task_list[PID].set__PPID(PPID);
			host._task_list[PID].set__name(process_name);
			PRINTD("HalParser:: Process added " + host._task_list[PID].get__name());
			host.signal_Process_added.emit(host._task_list[PID]);
		}
	}

}

/** 
 *  tokenize:	   
 *					Put into a vector @tokens tokens in same order of appeareance 
 *					that those tokens are concatenated in a line @str_orig. 
 *					Tokens in @str_oring are separated by @delimiters.
 *
 *  @str_orig:
 *					A string line 
 *  @delimiters:
 *					Delimiters
 *  @tokens:
 *					Vector where tokens get stored
 *  Returns:
 *
 *  Exceptions:
 *
 *  Example:
 *
 *					@str_orig = "si/pot:footoo:asitp:3345"
 *					@delimiter = ":"
 *					@tokens = "si/pot", "footoo", "asitp", "3345" 
 *
 */
void HalParser::tokenize(const DBus::String & str_orig,
                         const DBus::String & delimiters,
                         VectorString & tokens) {

    // Skip delimiters at beginning.
	DBus::String::size_type lastPos = str_orig.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	DBus::String::size_type pos     = str_orig.find_first_of(delimiters, lastPos);

	while (DBus::String::npos != pos || DBus::String::npos != lastPos) {
		// Found a token, add it to the vector.
		tokens.push_back(str_orig.substr(lastPos, pos - lastPos));
		// Skip delimiters.  Note the "not_of"
		lastPos = str_orig.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str_orig.find_first_of(delimiters, lastPos);
	}
}
