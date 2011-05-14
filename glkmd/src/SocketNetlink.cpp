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
    std::cout << "SocketNetlink::SocketNetlink [BEGIN]" << std::endl;
    m_valid=true;

    // using SOCK_RAW , but NETLINK obviates this parameter
    m_fd = socket(AF_NETLINK, SOCK_RAW, protocol);
    if (m_fd < 0)
    {
        std::cerr << errno << ":" << strerror(errno) << std::endl;
        m_valid=false;
//        return -1;
    }
    else
    {
        memset(&m_nladdr, 0, sizeof(struct sockaddr_nl));
        m_nladdr.nl_family = AF_NETLINK;
        //Destination process ==> pid = process(pid)
        //Destination kernel ==> pid = 0
        m_nladdr.nl_pid = 0;
        //    m_nladdr.nl_pid = getpid();
        //Destination kernel nl_groups = 0
        m_nladdr.nl_groups = 0;
        //    m_nladdr.nl_groups = groups;

        int ret;
        ret = bind(m_fd, (struct sockaddr *) &m_nladdr, sizeof(m_nladdr));
        if (ret < 0)
        {
            std::cerr << errno << ":" << strerror(errno) << std::endl;
            if (m_fd >= 0)
            {
                close(m_fd);
            }
            m_valid=false;
            //        return -1;
        }
    }
    std::cout << "SocketNetlink::SocketNetlink [END]" << std::endl;

/*    int
libnetlink_create_socket(int id, unsigned int groups)
{
    int ret;
    struct sockaddr_nl m_nladdr;

    m_fd = socket(AF_NETLINK, SOCK_RAW, id);
    if (m_fd < 0)
        return -1;

    memset(&m_nladdr, 0, sizeof(struct sockaddr_nl));
    m_nladdr.nl_family = AF_NETLINK;
    m_nladdr.nl_groups = groups;

    ret = bind(m_fd, (struct sockaddr *) &m_nladdr, sizeof(m_nladdr));
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
ssize_t SocketNetlink::send(const MessageNetlink& message)
{
    std::cout << "SocketNetlink::send [BEGIN]" << std::endl;
    if (!isValid())
    {
        std::cout << "SocketNetlink::send [END-ERROR]" << std::endl;
        return -1;
    }

    std::cout << "SocketNetlink::send [END]" << std::endl;
    return ::send(m_fd, message.get_nlmsghdr(), message.length(), 0);

/* DO NOT WORK
    / *
     struct msghdr {
         void    *   msg_name;   // Socket name
         int     msg_namelen;    // Length of name
         struct iovec *  msg_iov;    //Data blocks
         __kernel_size_t msg_iovlen; // Number of blocks
         void    *   msg_control;    // Per protocol magic (eg BSD file descriptor passing)
         __kernel_size_t msg_controllen; // Length of cmsg list
         unsigned    msg_flags;
     };
    * /

    struct iovec iov;
    iov.iov_base = (void *)message.get_nlmsghdr();
    iov.iov_len = message.length();

    struct msghdr msg;
    msg.msg_name = (void *)&(m_nladdr);
    msg.msg_namelen = sizeof(m_nladdr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    std::cout << "SocketNetlink::send [END]" << std::endl;
    return ::sendmsg(m_fd, &msg, 0);
*/
}


/**
 * recv - Bind a descriptor to their sockets structures
 * @m: 
 *
 */
ssize_t SocketNetlink::recv(MessageNetlink& m)
{
    std::cout << "SocketNetlink::recv [BEGIN]" << std::endl;
    if (!isValid())
    {
        std::cout << "SocketNetlink::recv [END-ERROR]" << std::endl;
        return -1;
    }

    int size=MAX_NETLINK_BUFFER;
    char data[size];
    int len=0;

    len=::recv(m_fd, (void *)data, size, 0);

    m.set_buf((void *)data,len);
    std::cout << "SocketNetlink::recv [END] len:" << len << std::endl;
    return len;
}
