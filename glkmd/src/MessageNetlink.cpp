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

#include <stdlib.h>
#include <iostream>
#include <cerrno>
#include <cstring>
// #include <sys/socket.h>
#include <netlink/netlink.h>
#include <netlink/msg.h>
#include <netlink/attr.h>

#include "MessageNetlink.hpp"



#define NLA_ALIGNTO     4
#define NLA_ALIGN(len)  (((len) + NLA_ALIGNTO - 1) & ~(NLA_ALIGNTO - 1))
//#define NLA_LENGTH(len) (NLA_HDRLEN + (len))
#define NLA_LENGTH(len) (NLA_ALIGN(sizeof(struct nlattr)) + (len))
#define NLA_DATA(nfa)   ((void *)(((char *)(nfa)) + NLA_LENGTH(0)))

// #define NLMSG_TAIL(nlh) (((struct nlmsghdr *) (nlh)) + NLMSG_ALIGN((nlh)->nlmsg_len))
#define NLMSG_TAIL(nlh) \
        (((void *) (nlh)) + NLMSG_ALIGN((nlh)->nlmsg_len))

/**
 * @brief constructor
 *
 * @param type ...
 * @param flags ...
 **/
MessageNetlink::MessageNetlink (const nl_msg_types_glkm &type,
                                const unsigned int &flags)
{
        std::cout << "MessageNetlink::MessageNetlink [BEGIN]" << std::endl;

        /*
         * Info taken from <linux/netlink.h>
         * #define NLM_F_REQUEST        1   / * It is request message.   * /
         * #define NLM_F_MULTI     2   / * Multipart message, terminated by NLMSG_DONE * /
         * #define NLM_F_ACK       4   / * Reply with ack, with zero or error code * /
         * #define NLM_F_ECHO      8   / * Echo this request        * /
         */
        int flags_used=NLM_F_REQUEST|NLM_F_ACK;
        if (flags!=0)
        {
                flags_used=flags;
        }
        m_type=type;
        m_message = nlmsg_alloc_simple(m_type,flags_used);

        if (!m_message)
        {
                std::cerr << errno << ":" << strerror (errno) << std::endl;
                //check calloc error
                //perror("calloc");
                //exit(EXIT_FAILURE);
                //return NULL;
        }

        add_AttributeU32ToMsg (NLGLKM_SIZE, MAX_NETLINK_BUFFER);

        std::cout << "MessageNetlink::MessageNetlink [END]" << std::endl;
}


/**
 * @brief destructor
 *
 **/
MessageNetlink::~MessageNetlink()
{
        nlmsg_free (m_message);
}


/**
 * length -
 *
 * @return
 */
// size_t MessageNetlink::length() const
// {
//         return nlmsg_total_size( nlmsg_datalen( nlmsg_hdr(m_message));
// }


/**
 * @brief ...
 *
 * @return nl_msg*
 **/
nl_msg * MessageNetlink::get_nlmsg()
{
        return m_message;
}


/**
 * @brief ...
 *
 * @return const nl_msg*
 **/
const nl_msg * MessageNetlink::get_nlmsg() const
{
        const nl_msg *copy = m_message;
        return copy;
}


/**
 * set_buf -
 * @arg buf:
 * @arg len:
 *
 * @return
 */
// void MessageNetlink::set_buf (void *buf, const size_t &len)
// {
//         std::cout << "MessageNetlink::set_buf [BEGIN]" << std::endl;
//
//         if (m_header)
//         {
//                 free (m_header);
//                 m_header = NULL;
//         }
//
//         int size = MAX_NETLINK_BUFFER;
//
//         m_header = (struct nlmsghdr *) calloc (sizeof (struct nlmsghdr) + size, 1);
//         if (!m_header)
//         {
//                 std::cerr << errno << ":" << strerror (errno) << std::endl;
//                 //check calloc error
//                 //perror("calloc");
//                 //exit(EXIT_FAILURE);
//                 //return NULL;
//         }
//         /*
//             char *bufbk=(char*)buf;
//             for (uint i=0; i<=len; i++)
//             {
//         //        printf("%02X", buf[i]);
//                 std::cout << std::hex << bufbk[i];
//             }
//             std::cout << std::endl;
//         */
//         memcpy ( (void *) m_header, buf, len);
//
//         std::cout << "MessageNetlink::set_buf [END] copied " << len << std::endl;
//
// }


/**
 * @brief ...
 *
 * @param processes ...
 * @return void
 **/
void MessageNetlink::operation_GetAllProcesses (std::vector<std::string> &processes)
{
//         struct nlmsgerr *err = (struct nlmsgerr *) NLMSG_DATA (m_header);
//         if ( (m_header->nlmsg_type == NLMSG_ERROR) &&
//                         (err->error != 0))
//         {
//                 std::cerr << errno << ":" << strerror (errno) << std::endl;
//                 //check  error
//                 //perror("");
//                 exit (EXIT_FAILURE);
//                 //return NULL;
//         }
//         else
//         {
//
//         }
}


/**
 * @brief ...
 *
 * @param type ...
 * @return bool
 **/
bool MessageNetlink::add_AttributeU32ToMsg (const nl_glkm_attr &type, const unsigned int &value)
{
        bool rt = true;
        std::cout << "MessageNetlink::add_AttributeU32ToMsg value:" << value << std::endl;
        
        if (nla_put_u32 (m_message, type, value) < 0)
        {
                std::cerr << errno << ":" << strerror (errno) << std::endl;
        }

        return rt;
}


/**
 * @brief ...
 *
 * @param type ...
 * @param data ...
 * @param alen ...
 * @return bool
 **/
bool MessageNetlink::add_MsgData (const int &type,
                                  void *data,
                                  const int &alen)
{
        bool rt = true;
        nlmsg_append (m_message, data, alen, 0);

        return rt;
}


