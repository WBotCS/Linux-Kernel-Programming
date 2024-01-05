#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/workqueue.h>
#include <linux/spinlock.h>
#include <linux/list.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include "kmlab_given.h"
#include <linux/uaccess.h>    // For copy_from_user and copy_to_user
#include <linux/slab.h>       // For kmalloc and kfree
#include <linux/sched.h>      // For current global variable of current process
#include <linux/timer.h>      // For timer_list


#define KMLAB_PROC_DIR "kmlab"
#define KMLAB_PROC_FILE "status"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yi"); // Change with your lastname
MODULE_DESCRIPTION("CPTS360 Lab 4");


struct store_list {
  int pid;
  struct list_head list;
};

static LIST_HEAD(pid_list);
static spinlock_t pid_lock;



static ssize_t kmRead(struct file *file, char __user *userBuf, size_t bufLength, loff_t *offset) {
// Allocate a buffer in kernel space to store data before copying it to user space
char *buf = kmalloc(4096, GFP_KERNEL);
int pos = 0;  // Position index for the buffer

struct list_head *ptr;
// Iterate through a list of items, presumably processes or tasks
list_for_each(ptr, &pid_list) {
// Accessing the actual data structure containing process details
struct store_list *p = list_entry(ptr, struct store_list, list);

// changes
int pid = p->pid;  // Fetch the process ID

unsigned long cpu_time;
get_cpu_use(pid, &cpu_time);  // Retrieve CPU usage for the process

// Check if there is enough buffer space left, break if not
if ((4096 - pos) < 1) break;

// Write the process information into the buffer, updating the position
pos += sprintf(buf + pos, " PIDS: %d CPU TIME: %u ms\n", pid, (jiffies_to_msecs(cpu_time)));

// Break if the buffer is full
if (pos >= 4096) break;
}

// Copy the buffer content to user space and return the number of bytes copied
return simple_read_from_buffer(userBuf, bufLength, offset, buf, pos);
}


static ssize_t kmWrite(struct file *file, const char __user *userBuf, size_t bufLength, loff_t *offset) {
// Local variables for storing the process ID and for error checking
int pid;
int echeck;
char buf[16]; // Buffer to store the user-provided data
struct store_list *p; // Pointer to a custom data structure

// Copy data from user space to kernel space, handling errors
if (copy_from_user(buf, userBuf, bufLength) != 0) {
return -EFAULT;
}
// Ensure that the buffer is null-terminated
buf[min(bufLength, sizeof(buf) - 1)] = '\0';

// Convert the buffer content (string) to an integer (process ID)
echeck = kstrtoint(buf, 10, &pid);
if (echeck) return -EINVAL; // Return error if conversion fails

// Lock a spinlock to ensure thread safety while modifying shared data
spin_lock(&pid_lock);

// Allocate memory for a new list element and set its process ID
p = kmalloc(sizeof(struct store_list), GFP_KERNEL);
p->pid = pid;

// Add the new element to the tail of the list
list_add_tail(&p->list, &pid_list);

// Unlock the spinlock after modification is complete
spin_unlock(&pid_lock);

// Return the number of bytes written
return bufLength;
}


static struct proc_ops proc_fops = {
  .proc_read = kmRead,
  .proc_write = kmWrite
};


static struct proc_dir_entry* proc_dir;
static struct proc_dir_entry* proc_status_file;

int __init kmlab_init(void) 
{

  #ifdef DEBUG
    pr_info("KMLAB MODULE LOADING\n");
  #endif
  // Insert your code here ...

// Create a new directory in the proc filesystem with the name "kmlab"
  proc_dir = proc_mkdir("kmlab", NULL);
    if (!proc_dir) {
        // If directory creation fails, return with an 'Out of Memory' error
        return -ENOMEM;
    }

// Create a new file within the "kmlab" directory named "status"
// The file permissions are set to 0666 (readable and writable by all users)
  proc_status_file = proc_create("status", 0666, proc_dir, &proc_fops);
    if (!proc_status_file) {
        // If file creation fails, remove the previously created "kmlab" directory
        remove_proc_entry("kmlab", NULL);
        // Return with an 'Out of Memory' error
        return -ENOMEM;
    }


  return 0;
}


void __exit kmlab_exit(void) 
{

  #ifdef DEBUG
  pr_info("KMLAB MODULE UNLOADING\n");
  #endif

  // Insert your code here ...


  remove_proc_entry("status", proc_dir);


  remove_proc_entry("kmlab", NULL);

  pr_info("kmlab Module Removed\n");
}

// Register init and exit functions
module_init(kmlab_init);
module_exit(kmlab_exit);