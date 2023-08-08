#include <linux/init.h> // For module init and exit
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h> // For fops
#include <linux/uaccess.h>
//#include <string.h> // Can't use it!

#define DEVICE_NAME "my_device"
MODULE_LICENSE("GPL");

#define arr_length 10

// FILE OPERATIONS
static int my_open(struct inode*, struct file*);
static int my_release(struct inode*, struct file*);
static ssize_t my_read(struct file*, char*, size_t, loff_t*);
//static ssize_t my_write(struct file*, char __user *, size_t, loff_t *);

static struct file_operations fops = {
   .open = my_open,
   .read = my_read,
   .release = my_release,
  // .write = my_write,
};

int accounts[arr_length];

// Why "static"? --> To bound it to the current file.
static int major; // Device major number. Driver reacts to this major number.

// Event --> LOAD
static int __init w_init(void) {
    int j;
    major = register_chrdev(0, DEVICE_NAME, &fops); // 0: dynamically assign a major number ||| name is displayed in /proc/devices ||| fops.
    if (major < 0) {
        printk(KERN_ALERT "my_device load failed.\n");
        return major;
    }
    
    for(j=0;j<arr_length;j++)
    {
    	accounts[j]=2000000;
    }
    
    printk(KERN_INFO "my_device module loaded: %d\n", major);
    return 0;
}

// Event --> UNLOAD
static void __exit w_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "my_device module unloaded.\n");
}

// Event --> OPEN
static int my_open(struct inode *inodep, struct file *filep) {
   printk(KERN_INFO "my_device opened.\n");
   return 0;
}

// Event --> CLOSE
static int my_release(struct inode *inodep, struct file *filep) {
   printk(KERN_INFO "my_device closed.\n");
   return 0;
}

// Event --> READ
static ssize_t my_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    
    int i;
    for(i=0;i<arr_length;i++)
    {
    	printk(KERN_INFO "%d,",accounts[i]);	
    }
    
    return 0;
}



static ssize_t q_write(struct file *filep, char __user *numbers_str, size_t len, loff_t *offset)
{
	char *currnum;
    	int numbers[4], i = 0;
    	char * reset="r";
	
	if(numbers_str==reset) // reset
	{
		for(i=0;i<arr_length;i++)
		{
			accounts[i]=2000000;
		}
	}
	
	else
	{
	
		while ((currnum=strsep(&numbers_str, " ,")) != NULL)
			numbers[i++] = simple_strtol(currnum,NULL,10);
		
		if(numbers[1]>=arr_length || numbers[2]>=arr_length)
			printk("invalid account number\n");
		else
		{
			
			if(numbers[0]==101) // enteghal
			{
				if(accounts[numbers[1]]>=numbers[3])
				{
					accounts[numbers[1]] -= numbers[3];
					accounts[numbers[2]] += numbers[3];
				}
				else printk("invalid amount\n");
			}
			
			else if(numbers[0]==118) // variz
			{
				if(numbers[1]!=45)
					printk("invalid format\n");
				else accounts[numbers[2]] += numbers[3];
			}
			
			else if(numbers[0]==98) // bardasht
			{
				if(numbers[2]!=45)
					printk("invalid format\n");
				else if(accounts[numbers[1]]>=numbers[3])
					accounts[numbers[3]] -= numbers[3];
				else printk("invalid amount\n");
			}
			
		}
	
	}
	return 0;
}




// Registering load and unload functions.
module_init(w_init);
module_exit(w_exit);
