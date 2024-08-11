#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/mutex.h>
#include <linux/uaccess.h> //copy_to_user, copy_from_user
#include <linux/io.h>      //ioremap, iounmap

#define DEVICE_NAME "sample_led"
#define CLASS_NAME  "led"
#define GPIO1_START_ADDR 0x4804C000
#define GPIO1_END_ADDR   0x4804e000
#define GPIO1_SIZE (GPIO1_END_ADDR - GPIO1_START_ADDR)
#define GPIO_SETDATAOUT 0x194
#define GPIO_CLEARDATAOUT 0x190
#define USR3 (1 << 24) // LED3

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Huylearnai");
MODULE_DESCRIPTION("A simple Linux char driver for controlling an LED");
MODULE_VERSION("1.0");

static int majorNumber;
static struct class* sampleLedClass = NULL;
static struct device* sampleLedDevice = NULL;
static DEFINE_MUTEX(led_mutex); // Mutex for concurrent access
static volatile void *gpio_addr;
static volatile unsigned int *gpio_setdataout_addr;
static volatile unsigned int *gpio_cleardataout_addr;
static bool led_on = false;

// Function prototypes
static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops =
{
    .open = dev_open,
    .read = dev_read,
    .write = dev_write,
    .release = dev_release,
};
static int __init sample_led_init(void){
    printk(KERN_INFO "SampleLED: Initializing the SampleLED LKM\n");

    // Register a major number
    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
    printk(KERN_INFO "SampleLED: registered correctly with major number %d\n", majorNumber);

    // Register the device class
    sampleLedClass = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(sampleLedClass)){
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(sampleLedClass);
    }
    printk(KERN_INFO "SampleLED: device class registered correctly\n");

    // Register the device driver
    sampleLedDevice = device_create(sampleLedClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    printk(KERN_INFO "SampleLED: device class created correctly\n");

    // Initialize GPIO mapping
    gpio_addr = ioremap(GPIO1_START_ADDR, GPIO1_SIZE);
    gpio_setdataout_addr   = gpio_addr + GPIO_SETDATAOUT;
    gpio_cleardataout_addr = gpio_addr + GPIO_CLEARDATAOUT;
    return 0;
}

static void __exit sample_led_exit(void){
    // Turn off the LED
    *gpio_cleardataout_addr = USR3;

    // Cleanup
    mutex_destroy(&led_mutex);
    iounmap(gpio_addr);
    device_destroy(sampleLedClass, MKDEV(majorNumber, 0));
    class_unregister(sampleLedClass);
    class_destroy(sampleLedClass);
    unregister_chrdev(majorNumber, DEVICE_NAME);
    printk(KERN_INFO "SampleLED: Goodbye from the LKM!\n");
}

static int dev_open(struct inode *inodep, struct file *filep){
    if (!mutex_trylock(&led_mutex)){ // Try to acquire the mutex (returns 0 on success)
        printk(KERN_ALERT "SampleLED: Device in use by another process");
        return -EBUSY;
    }
    printk(KERN_INFO "SampleLED: Device has been opened\n");
    return 0;
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
    char command;
    if (copy_from_user(&command, buffer, 1)){
        printk(KERN_ALERT "SampleLED: Failed to receive command from user\n");
        return -EFAULT;
    }

    if (command == '1') {
        *gpio_setdataout_addr = USR3;
        led_on = true;
        printk(KERN_INFO "SampleLED: LED turned ON\n");
    } else if (command == '0') {
        *gpio_cleardataout_addr = USR3;
        led_on = false;
        printk(KERN_INFO "SampleLED: LED turned OFF\n");
    } else {
        printk(KERN_ALERT "SampleLED: Invalid command received\n");
        return -EINVAL;
    }

    return len;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset){
    char status = led_on ? '1' : '0';
    int error_count = 0;
    error_count = copy_to_user(buffer, &status, 1);

    if (error_count == 0){
        printk(KERN_INFO "SampleLED: Sent LED status to the user\n");
        return 1; // The number of bytes read
    }
    else {
        printk(KERN_INFO "SampleLED: Failed to send LED status to the user\n");
        return -EFAULT; // Failed to read
    }
}
static int dev_release(struct inode *inodep, struct file *filep){
    mutex_unlock(&led_mutex); // Unlock the device
    printk(KERN_INFO "SampleLED: Device successfully closed\n");
    return 0;
}

module_init(sample_led_init);
module_exit(sample_led_exit);

