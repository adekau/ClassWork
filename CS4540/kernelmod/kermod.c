#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alex Dekau");
MODULE_DESCRIPTION("Hello World");

static int __init kermod_init (void) {
	printk(KERN_INFO "Hello world.\n");
	return 0;
}

static void __exit kermod_cleanup (void) {
	printk(KERN_INFO "Goodbye world.\n");
}

module_init(kermod_init);
module_exit(kermod_cleanup);
