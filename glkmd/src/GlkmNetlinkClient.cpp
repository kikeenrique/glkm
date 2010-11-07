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

#include "GlkmNetlinkClient.hpp"
#include "MessageNetlink.hpp"

GlkmNetlinkClient::GlkmNetlinkClient()
   : m_socketnl(NETLINK_GLKM)
{
	if (!m_socketnl.isValid())
	{
		//exception
		//print error
	}
}

std::vector<std::string> GlkmNetlinkClient::GetAllProcesses()
{
	//Prepare message payload and send
	MessageNetlink messageOut(NETLINK_GLKM_MSG_GetAllProcesses);
//messageOut.addAttr()
	if (ssize_t len=m_socketnl.send(messageOut) >= 0)
	{
		
		MessageNetlink messageIn(NETLINK_GLKM_MSG_GetAllProcesses);
		//receive answer and check for errors	
		if (ssize_t len=m_socketnl.recv(messageIn) >= 0)
		{
		}
	 	else
		{
			//print error
		}
	}
	else
	{
		//print error
	}
}