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

#ifndef _SOCKETNETLINK_HPP_
#define _SOCKETNETLINK_HPP_

extern "C"
{
#include <sys/socket.h>
#include <linux/netlink.h>
}

#ifndef NETLINK_GLKM
#define NETLINK_GLKM  20
#endif

class MessageNetlink;


class SocketNetlink
{
public:
    SocketNetlink(const unsigned int &protocol);
	~SocketNetlink();

	bool isValid();

	ssize_t send(const MessageNetlink& m);
	ssize_t recv(MessageNetlink& m);
protected:

private:
    SocketNetlink();
    SocketNetlink(const SocketNetlink&);

    int m_fd;
	bool m_valid;
	struct sockaddr_nl m_local;
};

/*

int libnetlink_create_socket(int id, unsigned int groups);
int libnetlink_destroy_socket(int id);
int libnetlink_send(int fd, struct nlmsghdr *nlh);
int libnetlink_recv(int fd, void *data, int size);

struct nlmsghdr *libnetlink_newmsg(int type, unsigned int flags, int size);

#define NLA_ALIGNTO     4
#define NLA_ALIGN(len)  (((len) + NLA_ALIGNTO - 1) & ~(NLA_ALIGNTO - 1))
#define NLA_LENGTH(len) (NLA_ALIGN(sizeof(struct nlattr)) + (len))
#define NLA_DATA(nfa)   ((void *)(((char *)(nfa)) + NLA_LENGTH(0)))

#define NLMSG_TAIL(nlh) \
(((void *) (nlh)) + NLMSG_ALIGN((nlh)->nlmsg_len))

#endif
*/
#endif // _SOCKETNETLINK_HPP_
