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
#	Enrique Garcia Alvarez (kike+gklm@eldemonionegro.com)
# License:
# 	GNU General Public License (http://www.gnu.org/copyleft/gpl.html)
#
#
# TODO:
#   +Revision of cleanup_module
#    This could get dangerous if there are still processes waiting in WaitQ_readers,
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
#include <linux/sched.h>	/* For putting processes to sleep and 
				   waking them up */

#include <asm/uaccess.h>        /* get_user and put_user */

#include <linux/device.h>       /* We want sysfs atributes<->reg.files */

/* 
 * module information stuff
 */

#define PROCMON_AUTHOR       "Enrique Garcia Alvarez <kikeenrique@users.sourceforge.net>"
#define PROCMON_DESCRIPTION  "A module for monitoring proccess"
//#define PROCMON_VERSION      "0.2-alpha"

MODULE_LICENSE("GPL");
MODULE_AUTHOR(PROCMON_AUTHOR);
MODULE_DESCRIPTION(PROCMON_DESCRIPTION);
MODULE_VERSION(PROCMON_VERSION);


/* 
 * some constant definitions
 */

#define DEVFS_MAX_SIZE		8092

/*
 * The buffer used to store characters for this module and it's size
 *
 */
static char devfs_buffer[DEVFS_MAX_SIZE];
static unsigned long devfs_buffer_size = 0;


/* 
 * The procces being monitorized and it's pid;
 * 
 */
static struct task_struct *p_proccesmonitorized;
static int monitor_pid = 1;


/* 
 * WaitQueue readers flag sincronization
 */
static int flag = 0;

/* 
 * Queue of processes who want read information
 */
DECLARE_WAIT_QUEUE_HEAD(WaitQ_readers);

static char b_task_list[4096]="";

/*
 * Attributes
struct device_attribute {
        struct attribute        attr;
        ssize_t (*show)(struct device *dev, 
	                struct device_attribute *attr, 
			char *buf);
        ssize_t (*store)(struct device *dev, 
	                 struct device_attribute *attr,
	                 const char *buf,
			 size_t count);
};
int device_create_file(struct device *device, struct device_attribute *);
void device_remove_file(struct device * dev, struct device_attribute *);

DEVICE_ATTR(_name, _mode, _show, _store);

 */

static ssize_t show_task_list(struct device * dev, struct device_attribute *attr, char * buf);
static ssize_t store_task_list(struct device * dev, struct device_attribute *attr, const char * buf, size_t count);

static DEVICE_ATTR(task_list, S_IWUSR | S_IRUGO, show_task_list, store_task_list);

/*
 show_task_list
 @dev
 @attr
 @char

	Outputs all tasks in current host.
	Format: name [pid] - [parent pid]
	
	TODO: It's suggested in kernel code to use get_task_comm, but compiler
	complains if used, so task->comm is used instead. 
*/
static ssize_t show_task_list(struct device * dev, struct device_attribute *attr, char * buf)
{
	struct task_struct *task;
//	char comm[TASK_COMM_LEN];
	unsigned long 	buf_size = 0;

	for_each_process(task)
	{
//		get_task_comm(comm, task);
//		printk("%s [%d] - [%d]\n", task->comm, task->pid, task->parent->pid);
		buf_size +=
			sprintf(&b_task_list[buf_size],
				"%s:%d:%d\n", 
				task->comm, 
				task->pid, 
				task->parent->pid);
	}	

	return snprintf(buf, PAGE_SIZE, "%s\n", &b_task_list[0]);
}

static ssize_t store_task_list(struct device * dev, struct device_attribute *attr, const char * buf, size_t count)
{
//	sscanf(buf, "%20s", b_task_list);
	return strnlen(buf, PAGE_SIZE);
}

/*TODO 
static struct attribute *procmon_sysfs_entries[] = {
	&dev_attr_task_list.attr,
	NULL,
};

static struct attribute_group procmon_attribute_group = {
	.attrs = procmon_sysfs_entries,
};
*/


/*
 * procmon_read is the function called when a process calls read() on
 * /dev/procmon.  
 * It writes to the buffer passed in the  read() call.
 *
 */

static ssize_t procmon_read(struct file *file,	/* see include/linux/fs.h   */
			     char *buffer,      /* The buffer to put data to 
						  (in the user segment)     */
			     size_t length,	/* The length of the buffer */
			     loff_t * offset)
{

	static int finished = 0;
	int ret;
	
	int i, is_signal;

	printk(KERN_INFO "CALL BEGIN --> procmon_read (/dev/procmon)\n");

	/* 
	 * Return 0 to signify end of file - that we have nothing 
	 * more to say at this point. 
	 * We should remember that we're working into kernel, that's why static 
	 * variable finished exists. Our code is "always" in memory, forever.
	 */
	if (finished) {
		finished = 0;
		printk(KERN_INFO "CALL END * --> procmon_read (/dev/procmon)\n");
		return 0;
	}

	/* 
	 * If the file's flags include O_NONBLOCK, it means the process doesn't
	 * want to wait for the file.  
	 */
	if ((file->f_flags & O_NONBLOCK)){
		printk(KERN_INFO "CALL NONBLOCK--> procmon_read (/dev/procmon)\n");

	} else {
		printk(KERN_INFO "CALL BLOCK--> procmon_read (/dev/procmon)\n");

		is_signal=0;
		/* 
		 * This function puts the current process, including any system
		 * calls, such as us, to sleep.  Execution will be resumed right
		 * after the function call, either because somebody called 
		 * wake_up(&WaitQ_readers) (only module_close does that, when the file 
		 * is closed) or when a signal, such as Ctrl-C, is sent 
		 * to the process.
		 * We use this call to control reads with events.
		 */
//		wait_event_interruptible(WaitQ_readers, flag != 0);
			
		/* 
		 * If we woke up because we got a signal we're not blocking, 
		 * return -EINTR (fail the system call).  This allows processes
		 * to be killed or stopped.
		 */
		
		for (i = 0; i < _NSIG_WORDS && !is_signal; i++)
			is_signal =
				current->pending.signal.sig[i] & ~current->
				blocked.sig[i];
		
		if (is_signal) {
			/* 
			 * It's important to put module_put(THIS_MODULE) here,
			 * because for processes where the open is interrupted
			 * there will never be a corresponding close. If we 
			 * don't decrement the usage count here, we will be 
			 * left with a positive usage count which we'll have no
			 * way to bring down to zero, giving us an immortal 
			 * module, which can only be killed by rebooting 
			 * the machine.
			 */
				module_put(THIS_MODULE);
			return -EINTR;
		}
		
		/* 
		 * If we got here, flag must be 1
		 */
		
		flag = 0;
	}	

	devfs_buffer_size = 0;	
	devfs_buffer_size += 
		sprintf(&devfs_buffer[devfs_buffer_size],
			"<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n");
	devfs_buffer_size += 
		sprintf(&devfs_buffer[devfs_buffer_size],
			"<information>\n");

	/* 
	   find_task_by_vpid is used now because find_task_by_pid was deprecated. 
	   More info about PID namespaces "PID namespaces in the 2.6.24 kernel: http://lwn.net/Articles/259217/"
	*/
	p_proccesmonitorized = find_task_by_vpid(monitor_pid);
	if (p_proccesmonitorized!=NULL){
		devfs_buffer_size += 
			sprintf(&devfs_buffer[devfs_buffer_size],
				"<%s>%d</%s>\n", "PID", monitor_pid, "PID");		
		devfs_buffer_size += 
			sprintf(&devfs_buffer[devfs_buffer_size],
				"<%s>%s</%s>\n", "name", p_proccesmonitorized->comm, "name");
	} else {
		devfs_buffer_size += 
			sprintf(&devfs_buffer[devfs_buffer_size],
				"<%s>%s%d</%s>\n", "error", "not currently existing PID", monitor_pid, "error");
	}
	
	devfs_buffer_size += 
		sprintf(&devfs_buffer[devfs_buffer_size],
			"</information>\n");

	memcpy(buffer, devfs_buffer, devfs_buffer_size);
	ret = devfs_buffer_size;

	finished = 1;

	printk(KERN_INFO "CALL END --> procmon_read (/dev/procmon)\n");

	return ret;		/* Return the number of bytes "read" */

}


/*
 * procmon_write is the function called when a process calls write() on
 * /dev/procmon.  
 * It reads from the buffer passed in the write() call.
 *
 */

static ssize_t procmon_write(struct file *file,	/* The file itself         */
			    const char *buffer,	/* The buffer with input   */
			    size_t length,	/* The buffer's length     */
			    loff_t * offset)    /* offset to file - ignore */
{

	printk(KERN_INFO "CALL BEGIN --> procmon_write (/dev/procmon)\n");

	/* get buffer size, if bigger truncated */
	devfs_buffer_size = length;
	if (devfs_buffer_size > DEVFS_MAX_SIZE ) {
		devfs_buffer_size = DEVFS_MAX_SIZE;
	}
	
	/* write data to the buffer */
	if ( copy_from_user(devfs_buffer, buffer, devfs_buffer_size) ) {
		return -EFAULT;
	} else {
		if (sscanf(devfs_buffer, "%d", &monitor_pid) <= 0){
			printk(KERN_INFO "ERROR!!!! Not valid PID input  --> procmon_write (/dev/procmon)\n");
		} else {
		        /* 
			   find_task_by_vpid is used now because find_task_by_pid was deprecated. 
			   More info about PID namespaces "PID namespaces in the 2.6.24 kernel: http://lwn.net/Articles/259217/"
			*/		  
			p_proccesmonitorized = find_task_by_vpid(monitor_pid);
			if (p_proccesmonitorized==NULL){
				printk(KERN_INFO "ERROR! Not PID found  --> procmon_write (/dev/procmon)\n");
			} else {
			        printk(KERN_INFO "WTF! monitor_pid, p_proccesmonitorized -> (%d,%d)\n", 
				       monitor_pid, p_proccesmonitorized->pid);
			}
		}
	}

	printk(KERN_INFO "CALL END --> procmon_write (/dev/procmon) pid[%d]\n", 
	       monitor_pid);
	
	return devfs_buffer_size;
}


/*
 * File operation we care about are read and write.
 */
static const struct file_operations procmon_fops = {
	.owner		= THIS_MODULE,
	.read		= procmon_read,
	.write          = procmon_write,
};

/* 
 * This function receives input from the user when the user writes to the /proc
 * file.
 */
static ssize_t module_writenotifica(struct file *file,	/* The file itself         */
			    const char *buffer,	/* The buffer with input   */
			    unsigned long length,	/* The buffer's length     */
			    void * offset)    /* offset to file - ignore */
{

  //	printk(KERN_INFO "LLAMADA INICIO --> write_notifica (/proc/%s)\n",  PROCFS_NOTIFICA);

	/* 
	 * Set flag to 1, so the processes in the WaitQ will be able to 
	 * unset flag back to zero and to read the file.
	 */		
	flag = 1;
	
	/* 
	 * Wake up all the processes in WaitQ, so if anybody is waiting for the
	 * file, they can have it.
	 */
	wake_up(&WaitQ_readers);

	//	printk(KERN_INFO "LLAMADA FIN --> write_notifica (/proc/%s)\n",	       PROCFS_NOTIFICA);
	
	return length;
}

static struct miscdevice procmon_device = {
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



/* 
 * Module initialization and cleanup 
 */

/* 
 * Initialize the module - register the proc file 
 */

int init_module()
{

	int ret;

	/*
	 * Create the "procmon" device in the /sys/class/misc directory.
	 * Udev will automatically create the /dev/procmon device using
	 * the default rules.
	 */
	ret = misc_register(&procmon_device);
	if (ret){		
		printk(KERN_ERR
		       "Unable to register \"procmon\" misc device\n");
		ret=-ENOMEM;
	}

	ret = device_create_file(procmon_device.this_device,
				 &dev_attr_task_list);
	
	printk(KERN_INFO "CREADO --> /dev/procmon created\n");	

	return ret;
}

/* 
 * Cleanup - unregister our files from /proc.
 * 
 */
void cleanup_module()
{
	misc_deregister(&procmon_device);

	printk(KERN_INFO "ELIMINADO --> /dev/procmon\n");

}
