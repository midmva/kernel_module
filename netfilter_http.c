#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_AUTHOR("Miruk Dmitry <midv@tut.by>");
MODULE_DESCRIPTION("Module for test task");
MODULE_LICENSE("GPL");

int Init(void)
{
    printk(KERN_INFO "Init my module\n");
    printk("Hello, World!\n");
    return 0;
}

void Exit(void)
{
    printk(KERN_INFO "Exit my module\n");
}

module_init(Init);
module_exit(Exit);
