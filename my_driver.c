#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Developer");
MODULE_DESCRIPTION("A simple character device driver with dynamic major allocation");
MODULE_VERSION("0.1");

static int major_number;
static struct class *my_class = NULL;
static struct device *my_device = NULL;

#define DEVICE_NAME "my_sensor"
#define CLASS_NAME "my_class"

static int my_open(struct inode *inodep, struct file *filep) {
    pr_info("my_driver: Device opened\n");
    return 0;
}

static int my_release(struct inode *inodep, struct file *filep) {
    pr_info("my_driver: Device closed\n");
    return 0;
}

static ssize_t my_read(struct file *filep, char __user *buffer, size_t len, loff_t *offset) {
    pr_info("my_driver: Read function called\n");
    return 0; // EOF
}

static ssize_t my_write(struct file *filep, const char __user *buffer, size_t len, loff_t *offset) {
    pr_info("my_driver: Write function called\n");
    return len;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .write = my_write,
};

static int __init my_driver_init(void) {
    pr_info("my_driver: Initializing on RT-kernel\n");

    // Dynamically allocate a major number
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        pr_err("my_driver: Failed to register a major number\n");
        return major_number;
    }
    pr_info("my_driver: Registered with major number %d\n", major_number);

    // Register the device class
    my_class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(my_class)) {
        unregister_chrdev(major_number, DEVICE_NAME);
        pr_err("my_driver: Failed to register device class\n");
        return PTR_ERR(my_class);
    }

    // Register the device driver
    my_device = device_create(my_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
    if (IS_ERR(my_device)) {
        class_destroy(my_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        pr_err("my_driver: Failed to create the device\n");
        return PTR_ERR(my_device);
    }

    pr_info("my_driver: Device node /dev/%s created successfully\n", DEVICE_NAME);
    return 0;
}

static void __exit my_driver_exit(void) {
    device_destroy(my_class, MKDEV(major_number, 0));
    class_destroy(my_class);
    unregister_chrdev(major_number, DEVICE_NAME);
    pr_info("my_driver: Unloaded successfully\n");
}

module_init(my_driver_init);
module_exit(my_driver_exit);
