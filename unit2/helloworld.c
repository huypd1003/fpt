#include <linux/module.h>
#include <linux/kernel.h>

int x = 100;  // Định nghĩa biến x
EXPORT_SYMBOL(x);  // Export biến x để các module khác có thể sử dụng

static int __init module_a_init(void)
{
    printk(KERN_INFO "Module A loaded, x = %d\n", x);
    return 0;
}

static void __exit module_a_exit(void)
{
    printk(KERN_INFO "Module A unloaded\n");
}

module_init(module_a_init);
module_exit(module_a_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Huypd");
MODULE_DESCRIPTION("Module A exporting variable x");

