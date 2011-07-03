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


#ifndef NETLINK_GLKM
#define NETLINK_GLKM  24
#endif

class MessageNetlink;

struct nl_sock;

/**
 * @brief ...
 **/

class SocketNetlink
{

public:
        /**
         * @brief ...
         *
         * @param protocol ...
         **/
        SocketNetlink (const unsigned int &protocol);
        /**
         * @brief ...
         *
         **/
        ~SocketNetlink();

        /**
         * @brief ...
         *
         * @return bool
         **/
        bool isValid();

        /**
         * @brief ...
         *
         * @param m ...
         * @return int
         **/
        int send (MessageNetlink& m);
        /**
         * @brief ...
         *
         * @param m ...
         * @return int
         **/
        int send_auto (MessageNetlink& m);
        /**
         * @brief ...
         *
         * @param m ...
         * @return int
         **/
        int recv (MessageNetlink& m);

protected:

private:
        SocketNetlink();
        SocketNetlink (const SocketNetlink&);

        bool m_valid;

        /**
         * @brief ...
         **/

        struct nl_sock *m_nlsock;
};

#endif // _SOCKETNETLINK_HPP_
