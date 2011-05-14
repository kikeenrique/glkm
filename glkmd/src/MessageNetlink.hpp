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
#define MAX_NETLINK_BUFFER 1024
#endif

enum nl_msg_types_glkm {
    NETLINK_GLKM_MSG_BASE=16,
    NETLINK_GLKM_MSG_GetAllProcesses,
    NETLINK_GLKM_MSG_MAX
};

struct msghdr;
struct nlmsghdr;

class MessageNetlink
{
    public:
        MessageNetlink(const nl_msg_types_glkm &type,
                       const unsigned int &flags=0);
        //    struct nlmsghdr *libnetlink_newmsg(int type, unsigned int flags, int size);
        ~MessageNetlink();

        //socket API -- send
        size_t length() const;
        //    void * get_buf() const;
        //socket API -- sendmsg
        //    const msghdr * get_msghdr() const;
        const nlmsghdr * get_nlmsghdr() const;

        //socket API -- recv
        void set_buf(void *buf,const size_t &len);
        //socket API -- recvmsg
        //todo

        void operation_GetAllProcesses(std::vector<std::string> &processes);

    protected:
        //Glkm Netlink API
        bool add_MsgType(const nl_msg_types_glkm &type);

        bool add_MsgData(const int &type,
                         const void *data,
                         const int &alen);
        //    libnetlink_addattr(struct nlmsghdr *nlh, int type, const void *data, int alen)

        struct nlmsghdr *m_header;
        //    struct msghdr m_msghdr;

    private:
        //    MessageNetlink();
        MessageNetlink(const MessageNetlink&);
};

#endif // _MESSAGENETLINK_HPP_
