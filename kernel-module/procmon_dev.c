/*#########################################################################
#
#  procmon_dev.c
# 
#	Project:
#	Desarrollo de herramientas de monitorización interna para Linux
#
###########################################################################
#
# Autor:
#	Enrique Garcia Alvarez (kikeenrique@users.sourceforge.net)
# License:
# 	GNU General Public License (http://www.gnu.org/copyleft/gpl.html)
#
#
# TODO:
#   +Revision of cleanup_module
#    This could get dangerous if there are still processes waiting in WaitQ,
#    because they are inside our read function, which will get unloaded. 
#
#
#
#      Creates two /dev files, one for reading proccess information 
# (blocking available), the other for writing and unblocking 
# blocked proccess(es).
###########################################################################*/

#include <linux/fs.h>           
#include <linux/init.h>         
#include <linux/miscdevice.h>   /* We work as a misc device */
#include <linux/module.h>       /* We work as a module */

#include <asm/uaccess.h>        /* get_user and put_user */

/* 
 * module information stuff
 */

#define PROCMON_AUTHOR       "Enrique Garcia Alvarez <kikeenrique@users.sourceforge.net>"
#define PROCMON_DESCRIPTION  "A module for monitoring proccess"
#define PROCMON_VERSION      "0.2-alpha"

MODULE_LICENSE("GPL");
MODULE_AUTHOR(PROCMON_AUTHOR);
MODULE_DESCRIPTION(PROCMON_DESCRIPTION);
MODULE_VERSION(PROCMON_VERSION);


/*
 * procmon_read is the function called when a process calls read() on
 * /dev/procmon.  It writes "Procmon, world!" to the buffer passed in the
 * read() call.
 */

static ssize_t procmon_read(struct file * file, char * buf, 
			  size_t count, loff_t *ppos)
{
	char *procmon_str = "Procmon, world!\n";
	int len = strlen(procmon_str); /* Don't include the null byte. */
	/*
	 * We only support reading the whole string at once.
	 */
	if (count < len)
		return -EINVAL;
	/*
	 * If file position is non-zero, then assume the string has
	 * been read and indicate there is no more data to be read.
	 */
	if (*ppos != 0)
		return 0;
	/*
	 * Besides copying the string to the user provided buffer,
	 * this function also checks that the user has permission to
	 * write to the buffer, that it is mapped, etc.
	 */
	if (copy_to_user(buf, procmon_str, len))
		return -EINVAL;
	/*
	 * Tell the user how much data we wrote.
	 */
	*ppos = len;

	return len;
}

/*
 * The only file operation we care about is read.
 */

static const struct file_operations procmon_fops = {
	.owner		= THIS_MODULE,
	.read		= procmon_read,
};

static struct miscdevice procmon_dev = {
	/*
	 * We don't care what minor number we end up with, so tell the
	 * kernel to just pick one.
	 */
	MISC_DYNAMIC_MINOR,
	/*
	 * Name ourselves /dev/procmon.
	 */
	"procmon",
	/*
	 * What functions to call when a program performs file
	 * operations on the device.
	 */
	&procmon_fops
};

static int __init
procmon_init(void)
{
	int ret;

	/*
	 * Create the "procmon" device in the /sys/class/misc directory.
	 * Udev will automatically create the /dev/procmon device using
	 * the default rules.
	 */
	ret = misc_register(&procmon_dev);
	if (ret)
		printk(KERN_ERR
		       "Unable to register \"Procmon, world!\" misc device\n");

	return ret;
}

module_init(procmon_init);

static void __exit
procmon_exit(void)
{
	misc_deregister(&procmon_dev);
}

module_exit(procmon_exit);
