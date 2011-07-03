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
// #include <sys/types.h>
// #include <sys/socket.h>
#include <netlink/netlink.h>
#include <netlink/msg.h>

#include "SocketNetlink.hpp"
#include "MessageNetlink.hpp"

#define TASK_COMM_LEN 16
void print_nla_to_string(struct nlattr *value)
{
        std::string rt;
        switch(value->nla_type)
        {
                case NLA_UNSPEC:
                        rt="UNSPEC";
                        break;
                case NLA_U8:
                        rt="U8";
                        break;
                case NLA_U16:
                        rt="U16";
                        break;
                case NLA_U32:
                {
                        uint res=nla_get_u32(value);
                        rt="U32";
                        std::cout << "print_nla_to_string attrlen:" << value->nla_len << " attrtype:"
                                  << rt << "(" << value->nla_type << "):" << res << std::endl;
                        break;
                }
                case NLA_U64:
                        rt="U64";
                        break;
                case NLA_STRING:
                {
//                         char res[TASK_COMM_LEN];
                        char *res=nla_get_string(value);
                        rt="STRING";
                        std::cout << "print_nla_to_string attrlen:" << value->nla_len << " attrtype:"
                                  << rt << "(" << value->nla_type << "):" << std::string(res) << std::endl;
                        
                        break;
                }
                case NLA_FLAG:
                        rt="FLAG";
                        break;
                        rt="";
                case NLA_MSECS:
                        rt="MSECS";
                        break;
                case NLA_NESTED:
                        rt="NESTED";
                        break;
/*                case NLA_NESTED_COMPAT:
                        rt="NESTED_COMPAT";
                        break;
                case NLA_NUL_STRING:
                        rt="NUL_STRING";
                        break;
                case NLA_BINARY:
                        rt="BINARY";
                        break;*/
                case __NLA_TYPE_MAX:
                        rt="TYPE_MAX";
                        break;
        }
}

/**
 * @brief SocketNetlink - Bind a descriptor to their sockets structures
 *
 * FIXME: since we are working with broadcast netlink sockets, group
 * should be passed as parameter!!
 *
 * @param protocol ...
 */
/**
 *
 **/
SocketNetlink::SocketNetlink (const unsigned int &protocol)
{
        std::cout << "SocketNetlink::SocketNetlink [BEGIN]" << std::endl;
        m_valid=true;

        m_nlsock = nl_socket_alloc();

        if (nl_connect (m_nlsock, protocol) < 0)
        {
                std::cerr << errno << ":" << strerror (errno) << std::endl;
                m_valid=false;
                //        return -1;
        }
        else
        {
        }

        std::cout << "SocketNetlink::SocketNetlink [END]" << std::endl;
}


/**
 * @brief Bind a descriptor to their sockets structures
 *
 **/
SocketNetlink::~SocketNetlink()
{
        nl_socket_free (m_nlsock);
}


bool SocketNetlink::isValid()
/**
 * @brief ...
 *
 * @return bool
 **/
{
        return m_valid;
}


/**
 * @brief Bind a descriptor to their sockets structures
 *
 * @param message ...
 * @return int
 **/
int SocketNetlink::send (MessageNetlink& message)
{
        std::cout << "SocketNetlink::send [BEGIN]" << std::endl;

        if (!isValid())
        {
                std::cout << "SocketNetlink::send [END-ERROR]" << std::endl;
                return -1;
        }

        std::cout << "SocketNetlink::send [END]" << std::endl;

        return nl_send (m_nlsock, message.get_nlmsg());
}


/**
 * @brief Bind a descriptor to their sockets structures
 *
 * @param message ...
 * @return int
 **/
int SocketNetlink::send_auto (MessageNetlink& message)
{
        std::cout << "SocketNetlink::send_auto [BEGIN]" << std::endl;

        if (!isValid())
        {
                std::cout << "SocketNetlink::send_auto [END-ERROR]" << std::endl;
                return -1;
        }

        std::cout << "SocketNetlink::send_auto [END]" << std::endl;

        return nl_send_auto (m_nlsock, message.get_nlmsg());
}


/**
 * @brief Bind a descriptor to their sockets structures
 *
 * @param m ...
 * @return int
 **/
int SocketNetlink::recv (MessageNetlink& m)
{
        std::cout << "SocketNetlink::recv [BEGIN]" << std::endl;

        if (!isValid())
        {
                std::cout << "SocketNetlink::recv [END-ERROR]" << std::endl;
                return -1;
        }

        unsigned char *buf = NULL;
        struct nlmsghdr *hdr = NULL;
        struct sockaddr_nl peer;
        memset (&peer,0,sizeof (peer));
        int len=0;
        struct ucred *creds = NULL;

        if (false)
        {
                len = nl_recvmsgs_default (m_nlsock);
        }
        else
        {
                len = nl_recv (m_nlsock, &peer, &buf, &creds);              
                hdr = (struct nlmsghdr *) buf;
                while (nlmsg_ok (hdr, len))
                {
                        std::cout << "SocketNetlink::recv len:" << len << std::endl;
                        //BEGIN Process message here...
                        struct nlattr *hdra = nlmsg_attrdata(hdr, 0);
                        int remaining = nlmsg_attrlen(hdr, 0);

                        while (nla_ok(hdra, remaining))
                        {
                                //BEGIN parse attribute here...
                                print_nla_to_string(hdra);
                                /*
                                int attrlen=nla_len(hdra);
                                int attrtype=nla_type(hdra);
                                std::cout << "SocketNetlink::recv attrlen:" << attrlen << " attrtype:"
                                          << nla_to_string(attrtype) << "(" << attrtype << ")" << std::endl;
                                          */
                                //END parse attribute here...
                                hdra = nla_next(hdra, &remaining);
                        };
                        //END Process message here...

                        hdr = nlmsg_next (hdr, &len);
                }
//         m.set_buf((void *)data,len);
        }
        std::cout << "SocketNetlink::recv [END]" << std::endl;

        return len;
}
