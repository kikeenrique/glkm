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

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/timer.h>
#include <linux/netlink.h>
#include <net/sock.h>
#include "nl_procmon.h"

static struct sock *nl_glkm;
/*
struct nl_glkm_obj {
 struct timer_list timeout;
 u32   msg_size;
 u32   dst_pid;
};
*/
#define RCV_SKB_FAIL(err) do { netlink_ack(skb, nlh, (err)); return; } while (0)

static struct sk_buff *nl_glkm_msg_alloc (int size,
                                          int type,
                                          gfp_t flags,
                                          const struct nlmsghdr *nlh_request)
{
        struct sk_buff *skb=NULL;
        struct nlmsghdr *nlh=NULL;
//         char *data;
        printk ("nl_glkm_msg_alloc.\n");

        // skb = alloc_skb(NLMSG_GOODSIZE, flags);
        skb = nlmsg_new (NLMSG_DEFAULT_SIZE, flags);

        if (skb == NULL)
                goto errout;

        /*
         * static inline struct nlmsghdr *nlmsg_put(struct sk_buff *skb,
         *                                          u32 pid, u32 seq,
         *                                          int type, int payload, int flags)*
         */
        /* we reserve space for an empty payload */
//         nlh = nlmsg_put (skb, 0, 0, type, size, 0);
        nlh = nlmsg_put (skb, nlh_request->nlmsg_pid, nlh_request->nlmsg_seq, type, 0, NLM_F_REQUEST);

        if (nlh == NULL)
                goto errout_nlmsg;

//         data = nlmsg_data (nlh);

        printk ("nl_glkm_msg_alloc.size %d\n", nlmsg_len (nlh));

        return skb;

errout_nlmsg:
        kfree (skb);

errout:
        return NULL;
}


static int nl_glkm_GetAllProcesses_pro_handler (const struct nlmsghdr *nlh_request,
                                                struct nlattr *cda[])
{
        int ret = 0;
        u32 msg_size;

        if (!cda[NLGLKM_SIZE])
                return -EINVAL;

        msg_size = nla_get_u32 (cda[NLGLKM_SIZE]);
        printk ("nl_glkm_GetAllProcesses_pro_handler. %d\n", msg_size);
        
        if (msg_size < 0 || msg_size > NLMSG_GOODSIZE)
                return -E2BIG;

        {

                struct sk_buff *skb;

                skb = nl_glkm_msg_alloc (msg_size,
                                         NETLINK_GLKM_MSG_GetAllProcesses,
                                         GFP_KERNEL,
                                         nlh_request);

                if (skb == NULL)
                {
                        /* continue but report to user-space that we
                         * are losing message due to allocation failures,
                         * not because of netlink itself */
                        ret = -ENOMEM;
                }

                /*
                    TODO: It's suggested in kernel code to use get_task_comm, but compiler
                    complains if used, so task->comm is used instead.
                */
                {

                        struct task_struct *task;
                        for_each_process (task)
                        {
                                //            printk("%s [%d] - [%d]\n", task->comm, task->pid, task->parent->pid);

                                if (nla_put_string (skb, NLA_STRING, task->comm) == -EMSGSIZE)
                                {
                                        printk (KERN_ERR "nl_glkm_GetAllProcesses_pro_handler. error in comm \n");
                                        ret = -EMSGSIZE;
                                }

                                if (nla_put_u32 (skb, NLA_U32, task->pid) == -EMSGSIZE)
                                {
                                        printk (KERN_ERR "nl_glkm_GetAllProcesses_pro_handler. error in pid \n");
                                        ret = -EMSGSIZE;
                                }

                                if (nla_put_u32 (skb, NLA_U32, task->parent->pid) == -EMSGSIZE)
                                {
                                        printk (KERN_ERR "nl_glkm_GetAllProcesses_pro_handler. error in ppid \n");
                                        ret = -EMSGSIZE;
                                }
                        }
                }

                /* no payload data is currently added */
                nlmsg_end (skb, nlmsg_hdr (skb));

                printk ("nl_glkm_GetAllProcesses_pro_handler. size %d\n", nlmsg_len (nlmsg_hdr (skb)));

                nlmsg_unicast (nl_glkm, skb, nlh_request->nlmsg_pid);

//    netlink_unicast(nl_glkm, skb, pid, MSG_DONTWAIT);
        }

        return ret;

        /*
         if (!cda[NLB_NUM] || !cda[NLGLKM_SIZE] || !cda[NLB_PID])
          return -EINVAL;
         msg_size = nla_get_u32(cda[NLGLKM_SIZE]);
         if (msg_size < 0 || msg_size > NLMSG_GOODSIZE)
          return -E2BIG;

         num_msgs = nla_get_u32(cda[NLB_NUM]);
         dst_pid = nla_get_u32(cda[NLB_PID]);


         for (i=0; i<num_msgs; i++) {
          struct sk_buff *skb;

          skb = nl_glkm_msg_alloc(msg_size,
             NETLINK_GLKM_MSG_GetAllProcesses,
             GFP_KERNEL);
          if (skb == NULL) {
           / * continue but report to user-space that we
            * are losing message due to allocation failures,
            * not because of netlink itself * /
           ret = -ENOMEM;
           continue;
          }
          netlink_unicast(nl_glkm, skb, dst_pid, MSG_DONTWAIT);
         }

         return ret;
        */
}

/*
static int nl_glkm_mcast_pro_handler(struct nlattr *cda[])
{
 int ret = 0;
 u32 num_msgs, msg_size, i;

 if (!cda[NLB_NUM] || !cda[NLGLKM_SIZE])
  return -EINVAL;

 msg_size = nla_get_u32(cda[NLGLKM_SIZE]);
 if (msg_size < 0 || msg_size > NLMSG_GOODSIZE)
  return -E2BIG;

 num_msgs = nla_get_u32(cda[NLB_NUM]);

 for (i=0; i<num_msgs; i++) {
  struct sk_buff *skb;

  skb = nl_glkm_msg_alloc(msg_size,
     NLBENCH_MSG_MULTICAST_PROCESS,
     GFP_KERNEL);
  if (skb == NULL) {
   / * continue but report to user-space that we
    * are losing message due to allocation failures,
    * not because of netlink itself * /
   ret = -ENOMEM;
   netlink_set_err(nl_glkm, 0, NLBENCH_GRP, -ENOBUFS);
   continue;
  }
  netlink_broadcast(nl_glkm, skb, 0, NLBENCH_GRP, GFP_KERNEL);
 }
 return ret;
}

static void nl_glkm_ucast(unsigned long foo)
{
 struct nl_glkm_obj *obj = (struct nl_glkm_obj *) foo;
 struct sk_buff *skb;

 skb = nl_glkm_msg_alloc(obj->msg_size,
    NLBENCH_MSG_UNICAST_INTERRUPT,
    GFP_ATOMIC);
 if (skb == NULL)
  goto errout;

 kfree(obj);
 netlink_unicast(nl_glkm, skb, obj->dst_pid, MSG_DONTWAIT);
errout:
 return;
}

static int nl_glkm_ucast_int_handler(struct nlattr *cda[])
{
 struct nl_glkm_obj *obj;
 u32 delay, random, num_msgs, msg_size, dst_pid, i;

 if (!cda[NLB_RANDOM] || !cda[NLB_NUM] ||
     !cda[NLGLKM_SIZE] || !cda[NLB_PID])
  return -EINVAL;

 random = nla_get_u32(cda[NLB_RANDOM]);

 msg_size = nla_get_u32(cda[NLGLKM_SIZE]);
 if (msg_size < 0 || msg_size > NLMSG_GOODSIZE)
  return -E2BIG;

 num_msgs = nla_get_u32(cda[NLB_NUM]);
 dst_pid = nla_get_u32(cda[NLB_PID]);

 for (i=0; i<num_msgs; i++) {
  obj = kzalloc(sizeof(struct nl_glkm_obj), GFP_KERNEL);
  if (obj == NULL)
   return -ENOMEM;

  / * use a random distribution to distribute timers * /
  if (random == 0)
   delay = 0;
  else
   delay = random32() % (random * HZ);

  obj->msg_size = msg_size;
  obj->dst_pid = dst_pid;
  setup_timer(&obj->timeout, nl_glkm_ucast, (unsigned long)obj);
  obj->timeout.expires = jiffies + delay;
  add_timer(&obj->timeout);
 }
 return 0;
}

static void nl_glkm_mcast(unsigned long foo)
{
 struct nl_glkm_obj *obj = (struct nl_glkm_obj *) foo;
 struct sk_buff *skb;
 printk("nl_glkm_mcast.\n");

 skb = nl_glkm_msg_alloc(obj->msg_size,
    NLBENCH_MSG_MULTICAST_INTERRUPT,
    GFP_ATOMIC);
 if (skb == NULL)
  goto errout;

 kfree(obj);
 netlink_broadcast(nl_glkm, skb, 0, NLBENCH_GRP, GFP_ATOMIC);
 return;
errout:
 netlink_set_err(nl_glkm, 0, NLBENCH_GRP, -ENOBUFS);
}

static int nl_glkm_mcast_int_handler(struct nlattr *cda[])
{
 struct nl_glkm_obj *obj;
 u32 delay, random, num_msgs, msg_size, i;
 printk("nl_glkm_mcast_int_handler.\n");

 if (!cda[NLB_RANDOM] || !cda[NLB_NUM] || !cda[NLGLKM_SIZE])
  return -EINVAL;

 random = nla_get_u32(cda[NLB_RANDOM]);

 msg_size = nla_get_u32(cda[NLGLKM_SIZE]);
 if (msg_size < 0 || msg_size > NLMSG_GOODSIZE)
  return -E2BIG;

 num_msgs = nla_get_u32(cda[NLB_NUM]);

 for (i=0; i<num_msgs; i++) {
  obj = kzalloc(sizeof(struct nl_glkm_obj), GFP_KERNEL);
  if (obj == NULL)
   return -ENOMEM;

  / * use a random distribution to distribute timers * /
  if (random == 0)
   delay = 0;
  else
   delay = random32() % (random * HZ);

  obj->msg_size = msg_size;
  setup_timer(&obj->timeout, nl_glkm_mcast, (unsigned long)obj);
  obj->timeout.expires = jiffies + delay;
  add_timer(&obj->timeout);
 }
 return 0;
}
*/
static int nl_glkm_rcv_handle (const struct nlmsghdr *nlh,
                               struct nlattr *cda[],
                               u32 pid)
{
        int ret = -EOPNOTSUPP;
        printk ("nl_glkm_rcv_handle.\n");

        switch (nlh->nlmsg_type)
        {

                case NETLINK_GLKM_MSG_GetAllProcesses:
                        ret = nl_glkm_GetAllProcesses_pro_handler (nlh, cda);
                        break;

                default:
                        printk ("nl_glkm_rcv_handle. nlmessage unknown type: %d.\n", nlh->nlmsg_type);
                        break;
        }

        return ret;
}

static int nl_glkm_rcv_msg (struct sk_buff *skb, struct nlmsghdr *nlh)
{
        int err;
        int min_len = NLMSG_SPACE (0);      
        struct nlattr *cda[NLGLKM_MAX+1];
        u32 pid = skb ? NETLINK_CB (skb).pid : 0;
        
        printk ("nl_glkm_rcv_msg. PID:%d\n", pid);

        if (security_netlink_recv (skb, CAP_NET_ADMIN))
        {
                printk (KERN_ERR "nl_glkm_rcv_msg. security. \n");
                RCV_SKB_FAIL (-EPERM);
                return -EPERM;
        }

        if (nlh->nlmsg_len < min_len)
        {
                printk (KERN_ERR "nl_glkm_rcv_msg. err min_len.\n");
                return -EINVAL;
        }

        {

                struct nlattr *attr = (void *) nlh + NLMSG_ALIGN (min_len);
                int attrlen = nlh->nlmsg_len - NLMSG_ALIGN (min_len);

                err = nla_parse (cda, NLGLKM_MAX, attr, attrlen, NULL);

                if (err < 0)
                {
                        printk (KERN_ERR "nl_glkm_rcv_msg. err.\n");
                        return err;
                }
        }

        return nl_glkm_rcv_handle (nlh, cda, pid);
}

static void
nl_glkm_rcv (struct sk_buff *skb)
{
        printk ("nl_glkm_rcv. BEGIN\n");
        netlink_rcv_skb (skb, &nl_glkm_rcv_msg);
        printk ("nl_glkm_rcv. END\n");
}

static int __init nl_glkm_init (void)
{
        nl_glkm = netlink_kernel_create (&init_net,
                                         NETLINK_GLKM,
                                         0,
                                         nl_glkm_rcv,
                                         NULL,
                                         THIS_MODULE);

        if (nl_glkm == NULL)
        {
                printk ("nl_procmon: cannot create netlink socket.\n");
                return -ENOMEM;
        }

        printk ("nl_procmon: loaded.\n");

        return 0;
}

static void __exit nl_glkm_exit (void)
{
        printk ("nl_procmon: removing module.\n");
        netlink_kernel_release (nl_glkm);
}

module_init (nl_glkm_init);
module_exit (nl_glkm_exit);

MODULE_AUTHOR ("Enrique Garcia Alvarez <kike+glkm@eldemonionegro.com>");
MODULE_LICENSE ("GPL");
