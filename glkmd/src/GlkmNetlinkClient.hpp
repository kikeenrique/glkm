/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * glkmd
 * Copyright (C) Enrique Garcia 2010 <kike+glkm@eldemonionegro.com>
 *
 * glkmd is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * glkmd is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _GLKMNETLINKCLIENT_HPP_
#define _GLKMNETLINKCLIENT_HPP_

#include <string>
#include <vector>

#include "SocketNetlink.hpp"

/**
 * @brief ...
 **/

class GlkmNetlinkClient
{

public:
        GlkmNetlinkClient();
        void GetAllProcesses (std::vector<std::string> &processes);

protected:
        SocketNetlink m_socketnl;

private:

};

#endif // _GLKMNETLINKCLIENT_HPP_

