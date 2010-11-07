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
#include <string.h>
#include <sys/socket.h>
#include <linux/netlink.h>

#include "MessageNetlink.hpp"

//#define NLA_ALIGNTO     4
//#define NLA_ALIGN(len)  (((len) + NLA_ALIGNTO - 1) & ~(NLA_ALIGNTO - 1))
#define NLA_LENGTH(len) (NLA_HDRLEN + (len))
//#define NLA_LENGTH(len) (NLA_ALIGN(sizeof(struct nlattr)) + (len))
#define NLA_DATA(nfa)   ((void *)(((char *)(nfa)) + NLA_LENGTH(0)))

#define NLMSG_TAIL(nlh) \
(((struct nlmsghdr *) (nlh)) + NLMSG_ALIGN((nlh)->nlmsg_len))


/**
 * MessageNetlink - constructor
 * @type:
 * @flags: 
 *
 */
MessageNetlink::MessageNetlink(const nl_msg_types_glkm &type,
                               const unsigned int &flags)
{
	int size=MAX_NETLINK_BUFFER;

	m_header = (struct nlmsghdr *) calloc(sizeof(struct nlmsghdr) + size, 1);
	if (!m_header)
	{
		//check calloc error
		//perror("calloc");
		//exit(EXIT_FAILURE);
        //return NULL;
	}

	m_header->nlmsg_len = NLMSG_LENGTH(0);
	m_header->nlmsg_flags = NLM_F_REQUEST | NLM_F_ACK | flags;
	add_MsgType(type);
}


/**
 * ~MessageNetlink - destructor
 *
 */
MessageNetlink::~MessageNetlink()
{
	if (m_header)
	{
		free(m_header);
	}
}


/**
 * length - 
 *
 */
size_t MessageNetlink::length() const
{
}


/**
 * get_buf - 
 *
 * /
void * MessageNetlink::get_buf() const
{
}
*/

/**
 * get_msghdr - 
 *
 */
/*const msghdr * MessageNetlink::get_msghdr() const
{
	return &m_msghdr;
}*/


/**
 * get_nlmsghdr - 
 *
 */
const nlmsghdr * MessageNetlink::get_nlmsghdr() const
{
	const nlmsghdr *copy=m_header;
	return copy;
}


/**
 * set_buf - 
 * @buf:
 * @len:
 *
 */
void MessageNetlink::set_buf(void *buf,const size_t &len)
{
}



/**
 * add_MsgType - constructor
 * @type:
 *
 */
bool MessageNetlink::add_MsgType(const nl_msg_types_glkm &type)
{
    m_header->nlmsg_type = type;
}


/**
 * add - constructor
 * @type:
 * @data: 
 * @alen:
 *
 */
bool MessageNetlink::add(const int &type,
                         const void *data,
                         const int &alen)
{
	struct nlattr *attr = (struct nlattr *) NLMSG_TAIL(m_header);
	int len = NLA_LENGTH(alen);

	attr->nla_type	= type;
	attr->nla_len	= len;
	memcpy(NLA_DATA(attr), data, alen);
	m_header->nlmsg_len = NLMSG_ALIGN(m_header->nlmsg_len) + NLA_ALIGN(len);
	
/*
void
libnetlink_addattr(struct nlmsghdr *nlh, int type, const void *data, int alen)
{
	struct nlattr *attr = NLMSG_TAIL(nlh);
	int len = NLA_LENGTH(alen);

	attr->nla_type	= type;
	attr->nla_len	= len;
	memcpy(NLA_DATA(attr), data, alen);
	nlh->nlmsg_len = NLMSG_ALIGN(nlh->nlmsg_len) + NLA_ALIGN(len);
}
*/	
}

