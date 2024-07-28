#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/spinlock.h>
#include <linux/kthread.h>

static int max_count = 500000000;
static int counter = 0;
static spinlock_t my_spinlock;
static struct task_struct *thread1;
static struct task_struct *thread2;
static int count_part(void *data) {
    int part = *(int *)data;
    int i;
    for (i = 0; i < part; i++) {
        spin_lock(&my_spinlock);
        counter++;
        spin_unlock(&my_spinlock);
    }
    return 0;
}
static int __init my_module_init(void) {
    int half = max_count ;
    printk(KERN_INFO "Initializing module\n");
    spin_lock_init(&my_spinlock);
    thread1 = kthread_run(count_part, &half, "thread1");
    if (IS_ERR(thread1)) {
        printk(KERN_ERR "Failed to create thread1\n");
        return PTR_ERR(thread1);
    }

    thread2 = kthread_run(count_part, &half, "thread2");
    if (IS_ERR(thread2)) {
        printk(KERN_ERR "Failed to create thread2\n");
        return PTR_ERR(thread2);
    }

    kthread_stop(thread1);
    kthread_stop(thread2);
    printk(KERN_INFO "Final counter value: %d\n", counter);

    return 0;
}

static void __exit my_module_exit(void) {
    printk(KERN_INFO "Exiting module\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Spinlock example module");
MODULE_AUTHOR("huypd");
