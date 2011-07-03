#ifndef _NLGLKM_H_
#define _NLGLKM_H_

#ifndef NETLINK_GLKM
#define NETLINK_GLKM 24
#endif

enum nlglkm_msg_types {
        NETLINK_GLKM_MSG_BASE = 16,
        NETLINK_GLKM_MSG_GetAllProcesses,
        NETLINK_GLKM_MSG_MAX
};

enum nl_glkm_msg_attr {
        NLGLKM_UNSPEC,
        NLGLKM_SIZE,    /* size of the message */
        __NLGLKM_MAX
};

#define NLGLKM_MAX     (__NLGLKM_MAX - 1)


#endif
