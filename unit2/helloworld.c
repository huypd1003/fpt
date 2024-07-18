#include <linux/module.h>
#include <linux/kernel.h>

int x = 100;
EXPORT_SYMBOL(x); 

static int __init module_a_init(void) {
    printk(KERN_INFO "Module 1 initialized with x = %d\n", x);
    return 0;
}

static void __exit module_a_exit(void) {
    printk(KERN_INFO "Module 1 exiting\n");
}

module_init(module_a_init);
module_exit(module_a_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("huypd");
MODULE_DESCRIPTION("Module 1 exporting variable x");

