/* 
 *
 * modulo.c
 *
 */
 
#include <linux/kernel.h>  /* We're doing kernel work */ 
#include <linux/module.h>  /* Specifically, a module */ 
#include <linux/proc_fs.h> /* Necessary because we use proc fs */ 
#include <asm/uaccess.h>   /* for get_user and put_user */ 
#include <linux/sched.h>	/* For putting processes to sleep and 
				   waking them up */

#define DRIVER_AUTHOR "Enrique Garcia Alvarez <kikeenrique@users.sourceforge.net>"
#define DRIVER_DESC   "A module for monitoring proccess"

/* 
 * module information stuff
 */
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);


#define PROCFS_MAX_SIZE		1024
#define PROCFS_NAME 		"monitor"

/**
 * This structure hold information about the /proc file
 *
 */
static struct proc_dir_entry *Our_Proc_File;

/**
 *
 * The procces being monitorized;
 */
static struct task_struct *monitor_p;

/**
 * The buffer used to store character for this module
 * The size of the buffer
 *
 */
static char procfs_buffer[PROCFS_MAX_SIZE];

static unsigned long procfs_buffer_size = 0;

/**
 * The buffer used to store character for this module
 * The size of the buffer
 *
 */

static int monitor_pid = 1;

/** 
 * This function is called when the /proc file is read
 *
 */
int procfile_read (char *buffer,
		   char **buffer_location,
		   off_t offset, 
		   int buffer_length, 
		   int *eof, 
		   void *data)
{
	int ret;
	
	printk(KERN_INFO "procfile_read (/proc/%s) called\n", PROCFS_NAME);
	
	if (offset > 0) {
		/* we have finished to read, return 0 */
		ret  = 0;
	} else {
		/* fill the buffer, return the buffer size */
		printk(KERN_INFO "procfile_read (/proc/%s)\n", PROCFS_NAME);
//		procfs_buffer_size = sprintf(procfs_buffer, "leyendo proceso con PID %d\n", current->pid);
		procfs_buffer_size = sprintf(procfs_buffer, "leyendo proceso con PID %d\n", monitor_pid);
		monitor_p = find_task_by_pid(monitor_pid);		
		if (monitor_p){
			procfs_buffer_size += sprintf(procfs_buffer, "leyendo proceso con nombre %s\n", monitor_p->comm);
		}		
		memcpy(buffer, procfs_buffer, procfs_buffer_size);
		ret = procfs_buffer_size;
	}

	return ret;
}

/**
 * This function is called when the /proc file is written
 *
 */
int procfile_write(struct file *file, 
		   const char *buffer, 
		   unsigned long count,
		   void *data)
{
//	int tmp=0;
	
	printk(KERN_INFO "procfile_write (/proc/%s) called\n", PROCFS_NAME);

	/* get buffer size */
	procfs_buffer_size = count;
	if (procfs_buffer_size > PROCFS_MAX_SIZE ) {
		procfs_buffer_size = PROCFS_MAX_SIZE;
	}
	
	/* write data to the buffer */
	if ( copy_from_user(procfs_buffer, buffer, procfs_buffer_size) ) {
		return -EFAULT;
	} else {
		sscanf(procfs_buffer, "%d", &monitor_pid);		
//		tmp=strtol(procfs_buffer);
		
	}
	

	return procfs_buffer_size;
}

/**
 *This function is called when the module is loaded
 *
 */
int init_module()
{
	/* create the /proc file */
	Our_Proc_File = create_proc_entry(PROCFS_NAME, 0644, NULL);
	
	if (Our_Proc_File == NULL) {
		remove_proc_entry(PROCFS_NAME, &proc_root);
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n",
			PROCFS_NAME);
		return -ENOMEM;
	}

	Our_Proc_File->read_proc  = procfile_read;
	Our_Proc_File->write_proc = procfile_write;
	Our_Proc_File->owner 	  = THIS_MODULE;
	Our_Proc_File->mode 	  = S_IFREG | S_IRUGO;
	Our_Proc_File->uid 	  = 0;
	Our_Proc_File->gid 	  = 0;
	Our_Proc_File->size 	  = 37;

	printk(KERN_INFO "/proc/%s created\n", PROCFS_NAME);	
	return 0;	/* everything is ok */
}

/**
 *This function is called when the module is unloaded
 *
 */
void cleanup_module()
{
	remove_proc_entry(PROCFS_NAME, &proc_root);
	printk(KERN_INFO "/proc/%s removed\n", PROCFS_NAME);
}
