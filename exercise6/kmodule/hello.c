
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Krithika");
MODULE_DESCRIPTION("a simple hello world kernel module");
MODULE_VERSION("1.0");

static int __init hello_init(void) {
    printk(KERN_INFO "hello, krithika kernel module is loaded!\n");
    return 0;
}

static void __exit hello_exit(void) {
    printk(KERN_INFO "krithika's kernel module removed.\n");
}

module_init(hello_init);
module_exit(hello_exit);
