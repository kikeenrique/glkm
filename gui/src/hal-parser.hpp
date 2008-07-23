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

#ifndef _HAL_PARSER_HPP_
#define _HAL_PARSER_HPP_

#include <dbusmm/types.h>

#include "utils.hpp"

class Host;
class Process;

class HalParser {
  public:
	HalParser();
	virtual ~HalParser();
	void parse_synchronize_processes(VectorString & hal_task_list, Host & host);

  private:
	void tokenize(const DBus::String & str_orig, const DBus::String & delimiters, VectorString & tokens);
};

#endif // _HAL_PARSER_HPP_
