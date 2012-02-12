#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/vmalloc.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/miscdevice.h>
#include <linux/input.h>
#include <asm/io.h>
#include <asm/uaccess.h>

#define MSG(m...) printk(KERN_INFO "CDDATA: " m "\n")

#define DEV_MAJOR 121
#define DEV_NAME  "debug"
//system call for open
static int cdata_open(struct inode *inode, struct file *filp)
{
	if(MINOR(inode->i_rdev) != 0){
		printk("error minor number");
		return -ENODEV;
	}
	printk(KERN_INFO "CDATA: open a device.\n");
	printk(KERN_INFO "minor number = %d", MINOR(inode->i_rdev));
	return 0;
}
//system call for close
static int cdata_close(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "CDATA: close a device.\n");
	return 0;
}
//system call for write
ssize_t cdata_write(struct file *filp, const char *buf, size_t size, loff_t *off)
{
	return 0;
}

//define file operations
static struct file_operations cdata_fops = {	
	owner:		THIS_MODULE,
	open:		cdata_open,
	release:	cdata_close,
	//read:		cdata_read,
	write:		cdata_write,
	//ioctl:		cdata_ioctl,
	
};


int cdata_init_module(void)
{
	MSG("CDATA V0.1.0");
	MSG("  Copyright (C) 2004 www.jollen.org");
	//register driver (VFS)
	if(register_chrdev(121, "cdata", &cdata_fops) < 0){
		printk(KERN_INFO "CDATA: couldn't register a device.\n");
		return -1;
	}
}

void cdata_cleanup_module(void)
{
	//unregister driver (VFS)
	unregister_chrdev(DEV_MAJOR, "cdata");
}

module_init(cdata_init_module);
module_exit(cdata_cleanup_module);

MODULE_LICENSE("GPL");
