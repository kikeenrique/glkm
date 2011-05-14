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

#include <iostream>
#include <cerrno>
#include <cstring>
#include "GlkmNetlinkClient.hpp"
#include "MessageNetlink.hpp"

GlkmNetlinkClient::GlkmNetlinkClient()
                : m_socketnl (NETLINK_GLKM)
{
        if (!m_socketnl.isValid())
        {
                //exception
                std::cerr << "GlkmNetlinkClient::GlkmNetlinkClient ERROR" << std::endl;
                std::cerr << strerror (errno) << std::endl;
        }
}

void GlkmNetlinkClient::GetAllProcesses (std::vector<std::string> &processes)
{
        std::cout << "GlkmNetlinkClient::GetAllProcesses [BEGIN]" << std::endl;
        //Prepare message payload and send
        MessageNetlink messageOut (NETLINK_GLKM_MSG_GetAllProcesses);
//messageOut.addAttr()
        ssize_t len_send = m_socketnl.send (messageOut);
        if (len_send >= 0)
        {
                std::cout << "GlkmNetlinkClient::GetAllProcesses send Message OK len:" << len_send << std::endl;
                MessageNetlink messageIn (NETLINK_GLKM_MSG_GetAllProcesses);
                //receive answer and check for errors
                ssize_t len_recv = m_socketnl.recv (messageIn);
                if (len_recv >= 0)
                {
                        std::cout << "GlkmNetlinkClient::GetAllProcesses recv Message OK len:" << len_recv << std::endl;
                        messageIn.operation_GetAllProcesses (processes);
                }
                else
                {
                        std::cerr << "GlkmNetlinkClient::GetAllProcesses recv Message ERROR" << std::endl;
                        std::cerr  << errno << ":" << strerror (errno) << std::endl;
                }
        }
        else
        {
                std::cerr << "GlkmNetlinkClient::GetAllProcesses send Message ERROR" << std::endl;
                std::cerr << errno << ":" << strerror (errno) << std::endl;
        }
        std::cout << "GlkmNetlinkClient::GetAllProcesses [END]" << std::endl;
}
