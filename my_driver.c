#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Justin Levesque");
MODULE_DESCRIPTION("A minimal RT-kernel character driver skeleton");
MODULE_VERSION("0.1");

static int __init my_driver_init(void) {
    pr_info("my_driver: initialized successfully on RT-kernel\n");
    return 0;
}

static void __exit my_driver_exit(void) {
    pr_info("my_driver: unloaded successfully\n");
}

module_init(my_driver_init);
module_exit(my_driver_exit);
