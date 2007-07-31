/*#########################################################################
#
#  modulo.c
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
# Based on documentacion at:
# http://tldp.org/LDP/lkmpg/2.6/html/lkmpg.html
#
# TODO:
#   +Revision of cleanup_module
#    This could get dangerous if there are still processes waiting in WaitQ,
#    because they are inside our read function, which will get unloaded. 
#
#
#
#      Creates two /proc files, one for reading proccess information 
# (blocking available), the other for writing and unblocking 
# blocked proccess(es).
###########################################################################*/

#include <linux/kernel.h>	/* We're doing kernel work */
#include <linux/module.h>	/* Specifically, a module */
#include <linux/proc_fs.h>	/* Necessary because we use proc fs */
#include <linux/sched.h>	/* For putting processes to sleep and 
				   waking them up */
#include <linux/file.h>	        /* For exporting file information */
#include <linux/mount.h>	        /* For exporting file information. PATH file information*/
#include <asm/uaccess.h>	/* for get_user and put_user */

#include <linux/list.h>

/* 
 * module information stuff
 */

#define DRIVER_AUTHOR "Enrique Garcia Alvarez <kikeenrique@users.sourceforge.net>"
#define DRIVER_DESC   "A module for monitoring proccess"

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);


#define PROCFS_MAX_SIZE		8092
#define PROCFS_NAME	"monitor"
#define PROCFS_NOTIFICA	"notifica"

/**
 * The procces being monitorized and it's pid;
 * 
 */
static struct task_struct *monitor_p;

static int monitor_pid = 1;


/**
 * The buffer used to store character for this module and it's size
 *
 */
static char procfs_buffer[PROCFS_MAX_SIZE];

static unsigned long procfs_buffer_size = 0;


/**
 * This structures hold information about the /proc files
 *
 */
static struct proc_dir_entry *monitor_Proc_File;
static struct proc_dir_entry *notifica_Proc_File;

/* 
 * 
 */
static int flag = 0;

/* 
 * Queue of processes who want reading information
 */
DECLARE_WAIT_QUEUE_HEAD(WaitQ);


/*
void
print_dentry(struct dentry *pdentry)
{

#define MAXPATH         2048

        struct dentry   parentdentry, *prevdentry;
        char            name[MAXPATH], *p=&name[MAXPATH-1];

        /
        ** check if valid dentry
        *
        if ( !pdentry->d_name.name      ||
              pdentry->d_name.len <= 0  ||
              pdentry->d_name.len >= MAXPATH)
                return;

	/
	** assemble the dentry-path string by
	** following the parent-chain towards the root-directory
	*
	parentdentry = *pdentry;

	name[MAXPATH-1] = 0;

	do{
		if (p != &name[MAXPATH-1])
			*--p = '/';
		
		p -= parentdentry.d_name.len;
		
		memcpy(p, parentdentry.d_name.name, parentdentry.d_name.len);
		
		prevdentry = parentdentry.d_parent;
		
		memcpy(&parentdentry, parentdentry.d_parent, sizeof (parentdentry));
		
	} while (prevdentry != parentdentry.d_parent);
	
	procfs_buffer_size += 
		sprintf(&procfs_buffer[procfs_buffer_size], 
			"%3d %08x %s \n",
			pdentry->d_count,
			pdentry->d_inode,
			p);
}
*/

void
print_path(struct vfsmount *pvfsmount, struct dentry *pdentry)
{

#define MAXPATH         2048

        struct dentry   parentdentry, *prevdentry;
        struct vfsmount   parentvfsmount;
 
        char            name[MAXPATH], *p=&name[MAXPATH-1];

        /*
        ** check if valid dentry
        */
        if ( !pdentry->d_name.name     ||
	     pdentry->d_name.len <= 0  ||
	     pdentry->d_name.len >= MAXPATH) {
		printk(KERN_INFO "ERROR! Not valid pdentry in print_path  --> (/proc/%s)\n", 
		       PROCFS_NAME);
                return;
	}
		      

	/*
	** assemble the dentry-path string by
	** following the parent-chain towards the root-directory
	*/
	parentdentry = *pdentry;
	parentvfsmount = *pvfsmount;	

	name[MAXPATH-1] = 0;

	do{
		do{
			if ( strcmp(parentdentry.d_name.name, "/") &&
			     (p != &name[MAXPATH-1]) )
				*--p = '/';
			
			p -= parentdentry.d_name.len;
			
			memcpy(p, parentdentry.d_name.name, parentdentry.d_name.len);
			prevdentry = parentdentry.d_parent;	
			memcpy(&parentdentry, parentdentry.d_parent, sizeof (parentdentry));			

		} while (prevdentry != parentdentry.d_parent);
		parentdentry = *parentvfsmount.mnt_mountpoint;
		memcpy(&parentvfsmount, parentvfsmount.mnt_parent, sizeof (parentvfsmount));
		
	} while (prevdentry != parentdentry.d_parent);
	
	procfs_buffer_size += 
		sprintf(&procfs_buffer[procfs_buffer_size],
			"<%s>%s</%s>\n", "fullpath", p, "fullpath");

}

/**
 * This function writes output to the user when the user reads the /proc file.
 *
 */
static ssize_t module_output(struct file *file,	/* see include/linux/fs.h   */
			     char *buffer,      /* The buffer to put data to 
						  (in the user segment)     */
			     size_t length,	/* The length of the buffer */
			     loff_t * offset)
{
	static int finished = 0;
	int ret;
	int filedesc;
	
	int i, is_sig;

	printk(KERN_INFO "LLAMADA INICIO --> module_output (/proc/%s)\n", PROCFS_NAME);

	/* 
	 * Return 0 to signify end of file - that we have nothing 
	 * more to say at this point. 
	 * We should remember that we're working into kernel, that's why static 
	 * variable finished exists. Our code is "always" in memory, forever.
	 */
	if (finished) {
		finished = 0;
		printk(KERN_INFO "LLAMADA FIN * --> module_output (/proc/%s)\n", PROCFS_NAME);
		return 0;
	}

	/* 
	 * If the file's flags include O_NONBLOCK, it means the process doesn't
	 * want to wait for the file.  
	 */
	if ((file->f_flags & O_NONBLOCK)){
		printk(KERN_INFO "LLAMADA NONBLOCK--> module_output (/proc/%s)\n", PROCFS_NAME);

	} else {
		printk(KERN_INFO "LLAMADA BLOCK--> module_output (/proc/%s)\n", PROCFS_NAME);

		is_sig=0;
		/* 
		 * This function puts the current process, including any system
		 * calls, such as us, to sleep.  Execution will be resumed right
		 * after the function call, either because somebody called 
		 * wake_up(&WaitQ) (only module_close does that, when the file 
		 * is closed) or when a signal, such as Ctrl-C, is sent 
		 * to the process
		 */
		wait_event_interruptible(WaitQ, flag != 0);
			
		/* 
		 * If we woke up because we got a signal we're not blocking, 
		 * return -EINTR (fail the system call).  This allows processes
		 * to be killed or stopped.
		 */
		
		for (i = 0; i < _NSIG_WORDS && !is_sig; i++)
			is_sig =
				current->pending.signal.sig[i] & ~current->
				blocked.sig[i];
		
		if (is_sig) {
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
	//monitor_pid=current->pid;
	procfs_buffer_size = 0;	
	procfs_buffer_size += 
		sprintf(&procfs_buffer[procfs_buffer_size],
			"<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n");
	procfs_buffer_size += 
		sprintf(&procfs_buffer[procfs_buffer_size],
			"<?xml-stylesheet type=\"text/css\" href=\"style.css\"?>\n");
/*	procfs_buffer_size += 
		sprintf(&procfs_buffer[procfs_buffer_size],
		"<?xml-stylesheet type=\"text/css\" href=\"style.css\"?>\n");
	procfs_buffer_size += 
		sprintf(&procfs_buffer[procfs_buffer_size],
		"<xs:schema xmlns:xs=\"http://www.w3.org/2001/XMLSchema\" targetNamespace=\"http://www.w3schools.com\" xmlns=\"http://www.w3schools.com\" elementFormDefault=\"qualified\">\n");
*/

	procfs_buffer_size += 
		sprintf(&procfs_buffer[procfs_buffer_size],
			"<information>\n");

	monitor_p = find_task_by_pid(monitor_pid);
	if (monitor_p!=NULL){
		procfs_buffer_size += 
			sprintf(&procfs_buffer[procfs_buffer_size],
				"<%s>%d</%s>\n", "PID", monitor_pid, "PID");
		
		procfs_buffer_size += 
			sprintf(&procfs_buffer[procfs_buffer_size],
				"<%s>%s</%s>\n", "name", monitor_p->comm, "name");
		if (monitor_p->files){
			/* We want to look for proccess files */
			procfs_buffer_size += 
				sprintf(&procfs_buffer[procfs_buffer_size],
					"<files>\n");

			procfs_buffer_size += 
				sprintf(&procfs_buffer[procfs_buffer_size],
					"<%s>%d</%s>\n", "count", monitor_p->files->count, "count");
			procfs_buffer_size += 
				sprintf(&procfs_buffer[procfs_buffer_size],
					"<%s>%d</%s>\n", "maxfds", monitor_p->files->fdt->max_fds , "maxfds");
			/*			procfs_buffer_size += 
				sprintf(&procfs_buffer[procfs_buffer_size],
				"<%s>%d</%s>\n", "maxfdset", monitor_p->files->max_fdset, "maxfdset");*/
			procfs_buffer_size += 
				sprintf(&procfs_buffer[procfs_buffer_size],
					"<%s>%d</%s>\n", "nextfd", monitor_p->files->next_fd, "nextfd");
			
			for (filedesc = 0; (filedesc < NR_OPEN_DEFAULT); filedesc++){
				/* We look for each file in use */
				if (monitor_p->files->fd_array[filedesc]){
					procfs_buffer_size += 
						sprintf(&procfs_buffer[procfs_buffer_size],
							"<file>\n");					
					procfs_buffer_size += 
						sprintf(&procfs_buffer[procfs_buffer_size],
							"<%s>%d</%s>\n", "fd_array", filedesc, "fd_array");
					//print_dentry (monitor_p->files->fd_array[filedesc]->f_path.fdentry);

//ADAPTING changes at http://lwn.net/Articles/206758/
					print_path (monitor_p->files->fd_array[filedesc]->f_path.mnt, monitor_p->files->fd_array[filedesc]->f_path.fdentry);

 					procfs_buffer_size += 
						sprintf(&procfs_buffer[procfs_buffer_size],
							"<%s>%d</%s>\n", "count", monitor_p->files->fd_array[filedesc]->f_count, "count");
 					procfs_buffer_size += 
						sprintf(&procfs_buffer[procfs_buffer_size],
							"<%s>%d</%s>\n", "flags", monitor_p->files->fd_array[filedesc]->f_flags, "flags");
 					procfs_buffer_size += 
						sprintf(&procfs_buffer[procfs_buffer_size],
							"<%s>%d</%s>\n", "mode", monitor_p->files->fd_array[filedesc]->f_mode, "mode");
					/* 					procfs_buffer_size += 
						sprintf(&procfs_buffer[procfs_buffer_size],
						"<%s>%d</%s>\n", "error", monitor_p->files->fd_array[filedesc]->f_error, "error");*/
 					procfs_buffer_size += 
						sprintf(&procfs_buffer[procfs_buffer_size],
							"<%s>%Ld </%s>\n", "position", monitor_p->files->fd_array[filedesc]->f_pos, "position");
 					procfs_buffer_size += 
						sprintf(&procfs_buffer[procfs_buffer_size],
							"<%s>%d</%s>\n", "UID", monitor_p->files->fd_array[filedesc]->f_uid, "UID");
 					procfs_buffer_size += 
						sprintf(&procfs_buffer[procfs_buffer_size],
							"<%s>%d</%s>\n", "GID", monitor_p->files->fd_array[filedesc]->f_gid, "GID");
 					procfs_buffer_size += 
					  /*						sprintf(&procfs_buffer[procfs_buffer_size],
											"<%s>%d</%s>\n", "maxcount", monitor_p->files->fd_array[filedesc]->f_maxcount, "maxcount");*/
 					procfs_buffer_size += 
						sprintf(&procfs_buffer[procfs_buffer_size],
							"<%s>%x</%s>\n", "vinode", monitor_p->files->fd_array[filedesc]->f_path.fdentry, "vinode");
 					procfs_buffer_size += 
						sprintf(&procfs_buffer[procfs_buffer_size],
							"<%s>%x</%s>\n", "pinode", monitor_p->files->fd_array[filedesc]->f_path.fdentry->d_inode, "pinode");

					procfs_buffer_size += 
						sprintf(&procfs_buffer[procfs_buffer_size],
							"</file>\n");
				}
			}
			procfs_buffer_size += 
				sprintf(&procfs_buffer[procfs_buffer_size],
					"</files>\n");
		}
	} else {
		procfs_buffer_size += 
			sprintf(&procfs_buffer[procfs_buffer_size],
				"<%s>%s%d</%s>\n", "error", "not currently existing PID", monitor_pid, "error");
	}
	
	procfs_buffer_size += 
		sprintf(&procfs_buffer[procfs_buffer_size],
			"</information>\n");

	memcpy(buffer, procfs_buffer, procfs_buffer_size);
	ret = procfs_buffer_size;

	finished = 1;

	printk(KERN_INFO "LLAMADA FIN --> module_output (/proc/%s)\n", PROCFS_NAME);

	return ret;		/* Return the number of bytes "read" */
}

/* 
 * This function receives input from the user when the user writes to the /proc
 * file.
 */
static ssize_t module_input(struct file *file,	/* The file itself         */
			    const char *buffer,	/* The buffer with input   */
			    size_t length,	/* The buffer's length     */
			    loff_t * offset)    /* offset to file - ignore */
{

	printk(KERN_INFO "LLAMADA INICIO --> module_input (/proc/%s)\n", PROCFS_NAME);

	/* get buffer size, if bigger truncated */
	procfs_buffer_size = length;
	if (procfs_buffer_size > PROCFS_MAX_SIZE ) {
		procfs_buffer_size = PROCFS_MAX_SIZE;
	}
	
	/* write data to the buffer */
	if ( copy_from_user(procfs_buffer, buffer, procfs_buffer_size) ) {
		return -EFAULT;
	} else {
		if (sscanf(procfs_buffer, "%d", &monitor_pid) <= 0){
			printk(KERN_INFO "ERROR!!!! Not valid PID input  --> module_input (/proc/%s)\n", 
			       PROCFS_NAME);
		} else {
			monitor_p = find_task_by_pid(monitor_pid);
			if (monitor_p==NULL){
				printk(KERN_INFO "ERROR! Not PID found  --> module_input (/proc/%s)\n", 
				       PROCFS_NAME);
			} else {
			        printk(KERN_INFO "WTF monitor_pid, monitor_p -> (%d,%d)\n", 
				       monitor_pid, monitor_p->pid);
			}
		}
	}

	printk(KERN_INFO "LLAMADA FIN --> module_input (/proc/%s) pid[%d]\n", 
	       PROCFS_NAME, monitor_pid);
	
	return procfs_buffer_size;
}

/* 
 * Called when the /proc file is opened 
 */
static int module_open(struct inode *inode, struct file *file)
{

	printk(KERN_INFO "LLAMADA --> module_open (/proc/%s)\n", PROCFS_NAME);

	/* 
	 * If the file's flags include O_NONBLOCK, it means the process doesn't
	 * want to wait for the file.  In this case, if the file is already 
	 * open, we should fail with -EAGAIN, meaning "you'll have to try 
	 * again", instead of blocking a process which would rather stay awake.
	 */
/*	if ((file->f_flags & O_NONBLOCK) && flag)
		return -EAGAIN;
*/

	/* 
	 * This is the correct place for try_module_get(THIS_MODULE) because 
	 * if a process is in the loop, which is within the kernel module,
	 * the kernel module must not be removed.
	 */
	try_module_get(THIS_MODULE);

	return 0;		/* Allow the access */
}

/* 
 * Called when the /proc file is closed 
 */
int module_close(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "LLAMADA --> module_close (/proc/%s)\n", PROCFS_NAME);

	module_put(THIS_MODULE);

	return 0;		/* success */
}

/*
 * This function decides whether to allow an operation (return zero) or not
 * allow it (return a non-zero which indicates why it is not allowed).
 *
 * The operation can be one of the following values:
 * 0 - Execute (run the "file" - meaningless in our case)
 * 2 - Write (input to the kernel module)
 * 4 - Read (output from the kernel module)
 *
 * This is the real function that checks file permissions. The permissions
 * returned by ls -l are for reference only, and can be overridden here.
 */
static int module_permission(struct inode *inode, int op, struct nameidata *nd)
{
	/* 
	 * We allow everybody to read from our module, but only root (uid 0)
	 * may write to it
	 */
	if (op == 4 || (op == 2 && current->euid == 0))
		return 0;

	/* 
	 * If it's anything else, access is denied 
	 */
	return -EACCES;
}

/* 
 * Structures to register as the /proc file, with pointers to all the relevant
 * functions.
 */

/* 
 * File operations for our proc file. This is where we place pointers to all
 * the functions called when somebody tries to do something to our file. NULL
 * means we don't want to deal with something.
 */
static struct file_operations File_Ops_4_monitor_Proc_File = {
	.read = module_output,	/* "read" from the file */
	.write = module_input,	/* "write" to the file */
	.open = module_open,	/* called when the /proc file is opened */
	.release = module_close,	/* called when it's closed */
};

/* 
 * Inode operations for our proc file.  We need it so we'll have somewhere to
 * specify the file operations structure we want to use, and the function we
 * use for permissions. It's also possible to specify functions to be called
 * for anything else which could be done to an inode (although we don't bother,
 * we just put NULL).
 */

static struct inode_operations Inode_Ops_4_monitor_Proc_File = {
	.permission = module_permission,	/* check for permissions */
};


/* 
 * This function receives input from the user when the user writes to the /proc
 * file.
 */
static ssize_t module_write(struct file *file,	/* The file itself         */
			    const char *buffer,	/* The buffer with input   */
			    unsigned long length,	/* The buffer's length     */
			    void * offset)    /* offset to file - ignore */
{

	printk(KERN_INFO "LLAMADA INICIO --> write_notifica (/proc/%s)\n",
	       PROCFS_NOTIFICA);

	/* 
	 * Set flag to 1, so the processes in the WaitQ will be able to 
	 * unset flag back to zero and to read the file.
	 */		
	flag = 1;
	
	/* 
	 * Wake up all the processes in WaitQ, so if anybody is waiting for the
	 * file, they can have it.
	 */
	wake_up(&WaitQ);

	printk(KERN_INFO "LLAMADA FIN --> write_notifica (/proc/%s)\n",
	       PROCFS_NOTIFICA);
	
	return length;
}

/* 
 * Module initialization and cleanup 
 */

/* 
 * Initialize the module - register the proc file 
 */

int init_module()
{

	monitor_Proc_File = create_proc_entry(PROCFS_NAME, 0644, NULL);
	
	if (monitor_Proc_File == NULL) {
		remove_proc_entry(PROCFS_NAME, &proc_root);
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n",
			PROCFS_NAME);
		return -ENOMEM;
	}
	
	monitor_Proc_File->owner = THIS_MODULE;
	monitor_Proc_File->proc_iops = &Inode_Ops_4_monitor_Proc_File;
	monitor_Proc_File->proc_fops = &File_Ops_4_monitor_Proc_File;
	/*
	  S_IWUSR => Write permission by owner
	  S_IRUGO (S_IRUSR|S_IRGRP|S_IROTH) => Read permission for everyone
	  S_IFREG => File is a regular file.
	 */
	monitor_Proc_File->mode = S_IFREG | S_IRUGO | S_IWUSR;
	monitor_Proc_File->uid = 0;
	monitor_Proc_File->gid = 0;

	printk(KERN_INFO "CREADO --> /proc/%s created\n", PROCFS_NAME);	

	
	notifica_Proc_File = create_proc_entry(PROCFS_NOTIFICA, 0200, NULL);

	if (notifica_Proc_File == NULL) {
		remove_proc_entry(PROCFS_NOTIFICA, monitor_Proc_File);
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n",
		       PROCFS_NOTIFICA);
		return -ENOMEM;
	}
	
	notifica_Proc_File->owner = THIS_MODULE;
	notifica_Proc_File->write_proc = module_write;
	/*
	  S_IWUSR => Write permission by owner
	  S_IFREG => File is a regular file.
	 */
	notifica_Proc_File->mode = S_IFREG | S_IWUSR;
	notifica_Proc_File->uid = 0;
	notifica_Proc_File->gid = 0;
	
	printk(KERN_INFO "CREADO --> /proc/%s created\n",
	       PROCFS_NOTIFICA);

	return 0;
}

/* 
 * Cleanup - unregister our files from /proc.
 * 
 */
void cleanup_module()
{
	remove_proc_entry(PROCFS_NAME, &proc_root);

	printk(KERN_INFO "ELIMINADO --> /proc/%s\n", PROCFS_NAME);

	remove_proc_entry(PROCFS_NOTIFICA, &proc_root);

	printk(KERN_INFO "ELIMINADO --> /proc/%s\n", PROCFS_NOTIFICA);

}
