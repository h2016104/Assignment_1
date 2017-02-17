#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/time.h>

struct timeval TV;
int i,j,ans,ret;
int data, data2;

int ex_open(struct inode *pinode, struct file *pfile)
{ printk(KERN_ALERT"inside the %s function\n",__FUNCTION__);
  return 0;
}
ssize_t ex_read(struct file *pfile, int __user *buffer, size_t length, loff_t *offset)
{ printk(KERN_ALERT"inside the %s function\n",__FUNCTION__);
  do_gettimeofday(&TV);
  j = TV.tv_sec;
  j = j%60;
  i = (7*j) % 101;
  ans = ((i-1)%10)+1;
  data2 = (ans*data)/9;
  ret = copy_to_user(buffer, &data2, sizeof(data2));
  printk(KERN_ALERT"ret=%d\n",ret); 
  return ret;
}
ssize_t ex_write(struct file *pfile, const int __user *buffer, size_t length, loff_t *offset)
{ printk(KERN_ALERT"inside the %s function\n",__FUNCTION__);
  ret = copy_from_user(&data, buffer, length);
  return ret;
}
int ex_close(struct inode *pinode, struct file *pfile)
{ printk(KERN_ALERT"inside the %s function\n",__FUNCTION__);
  return 0;
}

struct file_operations ex_file_operations ={
   .owner   = THIS_MODULE,
   .open    = ex_open,
   .read    = ex_read,  
   .write   = ex_write,
   .release = ex_close,
 };

int __init ex_init(void)
{  printk(KERN_ALERT"inside the %s function\n",__FUNCTION__);
   register_chrdev(240, "simple char drv", &ex_file_operations);
   return 0;
}

int __exit ex_exit(void)
{  printk(KERN_ALERT"inside the %s function\n",__FUNCTION__);
   unregister_chrdev(240, "simple char drv");
   return 0;
}

module_init(ex_init);
module_exit(ex_exit);
