#ifndef _NLGLKM_H_
#define _NLGLKM_H_

#ifndef NETLINK_GLKM
#define NETLINK_GLKM 24
#endif

enum nlbench_msg_types {
	NETLINK_GLKM_MSG_BASE = 16,
	NETLINK_GLKM_MSG_GetAllProcesses,
	NETLINK_GLKM_MSG_MAX
};

enum nl_glkm_attr {
	NLB_UNSPEC,
	NLB_SIZE,		/* size of the message */
	NLB_NUM,		/* number of messages */
	NLB_PID,		/* destination port id for unicast */
	__NLB_MAX
};

#define NLB_MAX			(__NLB_MAX - 1)


#endif
