#include <linux/module.h>
#include <linux/kernel.h>

extern int x;  // Khai báo extern biến x từ Module A

static int __init module_b_init(void)
{
    printk(KERN_INFO "Module B loaded, x = %d\n", x);
    return 0;
}

static void __exit module_b_exit(void)
{
    printk(KERN_INFO "Module B unloaded\n");
}

module_init(module_b_init);
module_exit(module_b_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Huypd");
MODULE_DESCRIPTION("Module B using variable x from Module A");

