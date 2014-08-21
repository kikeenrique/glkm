/*
 * glkmd
 * MessageNetlink.cpp
 *
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

#ifndef _MESSAGENETLINK_HPP_
#define _MESSAGENETLINK_HPP_

#include <cstddef>
#include <vector>

#ifndef MAX_NETLINK_BUFFER
#define MAX_NETLINK_BUFFER 3000
#endif

/**
 * @brief ...
 **/
enum nl_msg_types_glkm
{
        NETLINK_GLKM_MSG_BASE=16,
        NETLINK_GLKM_MSG_GetAllProcesses,
        NETLINK_GLKM_MSG_MAX
};

enum nl_glkm_attr {
        NLGLKM_UNSPEC,
        NLGLKM_SIZE,       /* size of the message */
        __NLGLKM_MAX
};

struct nl_msg;

/**
 * @brief ...
 **/

class MessageNetlink
{

public:
        MessageNetlink (const nl_msg_types_glkm &type,
                        const unsigned int &flags=0);
        ~MessageNetlink();

        /*        ///socket API -- send
                size_t length() const;
                ///    void * get_buf() const;
        */
        ///socket API -- sendmsg
        nl_msg * get_nlmsg();
        const nl_msg * get_nlmsg() const;

        ///socket API -- recv
        void set_buf (void *buf,const size_t &len);
        ///socket API -- recvmsg
        ///todo

        ///
        void operation_GetAllProcesses (std::vector<std::string> &processes);

protected:

        nl_msg_types_glkm m_type;

        struct nl_msg *m_message;

        unsigned char *m_buf;
        int m_len;

        ///Glkm Netlink API
        ///
        bool add_AttributeU32ToMsg (const nl_glkm_attr &type, const unsigned int &value);
        ///
        bool add_MsgData (const int &type,
                          void *data,
                          const int &alen);
        ///
        MessageNetlink (const MessageNetlink&);
        ///
        MessageNetlink& operator= (const MessageNetlink&);
};

#endif // _MESSAGENETLINK_HPP_





