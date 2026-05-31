#include <linux/module.h>    // 모듈 필수 헤더
#include <linux/fs.h>        // file_operations
#include <linux/cdev.h>      // cdev 구조체
#include <linux/uaccess.h>   // copy_to_user, copy_from_user
#include <linux/init.h>

static int __init mydriver_init(void) {
    printk(KERN_INFO "Log, info! \n");
    printk(KERN_WARNING "Log, warn! \n");
    printk(KERN_ALERT "Log, alter! \n");
    printk(KERN_INFO "Log, info! \n");
    printk(KERN_DEBUG "Log, debug! \n");
    return 0;
}

static void __exit mydriver_exit(void) {
    pr_info("log driver unloaded, info\n");
    pr_err("log driver unloaded, err\n");
    pr_emerg("log driver unloaded, emerg\n");
}

module_init(mydriver_init);
module_exit(mydriver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("sehyeon");
MODULE_DESCRIPTION("Simple character device driver");
