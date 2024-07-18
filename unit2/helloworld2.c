#include <linux/module.h>
#include <linux/kernel.h>

extern int x;  // Khai báo extern biến x từ module 1

static int __init module_b_init(void) {
    printk(KERN_INFO "Module 2 initialized with x = %d\n", x);
    return 0;
}

static void __exit module_b_exit(void) {
    printk(KERN_INFO "Module 2 exiting\n");
}

module_init(module_b_init);
module_exit(module_b_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Huypd");
MODULE_DESCRIPTION("Module 2 using variable x from Module 1");

