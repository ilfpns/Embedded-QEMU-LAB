#include <linux/module.h>    // 모듈 필수 헤더
#include <linux/fs.h>        // file_operations
#include <linux/cdev.h>      // cdev 구조체
#include <linux/uaccess.h>   // copy_to_user, copy_from_user

#define DRIVER_NAME "mydriver"
#define MSG "Hello from kernel driver!\n"

static int major;            // 디바이스 번호 (커널이 자동 할당)
static struct cdev my_cdev;  // 캐릭터 디바이스 구조체

static const struct file_operations myfops = {
    .owner   = THIS_MODULE,
    .read    = logread,
    .open    = myopen,
    .release = myrelease,
};
    
static int __init mydriver_init(void) {
    dev_t dev;
    alloc_chrdev_region(&dev, 0, 1, DRIVER_NAME);
    major = MAJOR(dev);

    cdev_init(&my_cdev, &myfops);
    cdev_add(&my_cdev, dev, 1);

    pr_info("major number :  %d\n", major);
    return 0;
}

static void __exit mydriver_exit(void) {
    cdev_del(&my_cdev);
    unregister_chrdev_region(MKDEV(major, 0), 1);
    pr_alter("log driver unloaded.\n");
}

module_init(mydriver_init);
module_exit(mydriver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("sehyeon");
MODULE_DESCRIPTION("Simple character device driver");
