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
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/netlink.h>

#include "SocketNetlink.hpp"
#include "MessageNetlink.hpp"


/**
 * SocketNetlink - Bind a descriptor to their sockets structures
 * @protocol: 
 *
 * FIXME: since we are working with broadcast netlink sockets, group
 * should be passed as parameter!!
 */
SocketNetlink::SocketNetlink(const unsigned int &protocol)
{
	m_valid=true;

	// using SOCK_RAW , but NETLINK obviates this parameter
	m_fd = socket(AF_NETLINK, SOCK_RAW, protocol);
	if (m_fd < 0)
	{
//		perror("socket:");
		m_valid=false;
//		return -1;
	}
	else
	{
		memset(&m_local, 0, sizeof(struct sockaddr_nl));
		m_local.nl_family = AF_NETLINK;
		//Destination kernel pid = 0
		m_local.nl_pid = 0;
		//	m_local.nl_pid = getpid();
		//Destination kernel nl_groups = 0
		m_local.nl_groups = 0;
		//	m_local.nl_groups = groups;

		int ret;
		ret = bind(m_fd, (struct sockaddr *) &m_local, sizeof(m_local));
		if (ret < 0)
		{
			//		perror("bind:");
			if (m_fd >= 0)
			{
				close(m_fd);
			}
			m_valid=false;
			//		return -1;
		}
	}

/*	int
libnetlink_create_socket(int id, unsigned int groups)
{
	int ret;
	struct sockaddr_nl m_local;

	m_fd = socket(AF_NETLINK, SOCK_RAW, id);
	if (m_fd < 0)
		return -1;

	memset(&m_local, 0, sizeof(struct sockaddr_nl));
	m_local.nl_family = AF_NETLINK;
	m_local.nl_groups = groups;

	ret = bind(m_fd, (struct sockaddr *) &m_local, sizeof(m_local));
	if (ret < 0)
	{
		m_valid=false;
		return -1;
	}

	return fd;
}
*/
}


/**
 * ~SocketNetlink - Bind a descriptor to their sockets structures
 */
SocketNetlink::~SocketNetlink()
{
	if (m_fd >= 0)
	{
		close(m_fd);
	}
}


/**
 * valid - 
 *
 */
bool SocketNetlink::isValid()
{
	return m_valid;
}


/**
 * send - Bind a descriptor to their sockets structures
 * @m: 
 *
 */
ssize_t SocketNetlink::send(const MessageNetlink& m)
{
//	return ::send(m_fd, m.get_buf(), m.length(), 0);
	struct msghdr msg;
	msg.msg_name = (void *)&(m_local);
	msg.msg_namelen = sizeof(m_local);

	struct iovec iov;
	iov.iov_base = (void *)m.get_nlmsghdr();
	iov.iov_len = m.length();

	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	
//	return ::sendmsg(m_fd, m.get_msghdr(), 0);
	return ::sendmsg(m_fd, &msg, 0);
}


/**
 * recv - Bind a descriptor to their sockets structures
 * @m: 
 *
 */
ssize_t SocketNetlink::recv(MessageNetlink& m)
{
	int size=1024;
	char data[size];
	int len=0;
	
	len=::recv(m_fd, (void *)&data, size, 0);

	return len;
}
