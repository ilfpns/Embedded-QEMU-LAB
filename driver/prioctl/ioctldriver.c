#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include "myioctl.h"

#define DRIVER_NAME "mydriver"

static int major;
static struct cdev my_cdev;
static int stored_value = 0;

static int my_open(struct inode *inode, struct file *file)
{
    return 0;   /* 열기만 하면 됨, 로그도 필요 없음 */
}

static int my_release(struct inode *inode, struct file *file)
{
    return 0;   /* 닫기만 하면 됨 */
}

static long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int val;

    switch (cmd) {

    case MYDRV_IOCTL_SET_VALUE:
        if (copy_from_user(&val, (int __user *)arg, sizeof(int)))
            return -EFAULT;
        stored_value = val;
        pr_info("mydriver: SET_VALUE = %d\n", stored_value);
        break;

    case MYDRV_IOCTL_GET_VALUE:
        if (copy_to_user((int __user *)arg, &stored_value, sizeof(int)))
            return -EFAULT;
        pr_info("mydriver: GET_VALUE = %d\n", stored_value);
        break;

    case MYDRV_IOCTL_RESET:
        stored_value = 0;
        pr_info("mydriver: RESET, value = %d\n", stored_value);
        break;

    default:
        return -EINVAL;
    }

    return 0;
}

static const struct file_operations my_fops = {
    .owner          = THIS_MODULE,
    .open           = my_open,       /* 필수 */
    .release        = my_release,    /* 필수 */
    .unlocked_ioctl = my_ioctl,
};

static int __init mydriver_init(void)
{
    dev_t dev;
    alloc_chrdev_region(&dev, 0, 1, DRIVER_NAME);
    major = MAJOR(dev);
    cdev_init(&my_cdev, &my_fops);
    cdev_add(&my_cdev, dev, 1);
    pr_info("mydriver: loaded! major=%d\n", major);
    pr_info("mydriver: mknod /dev/mydriver c %d 0\n", major);
    return 0;
}

static void __exit mydriver_exit(void)
{
    cdev_del(&my_cdev);
    unregister_chrdev_region(MKDEV(major, 0), 1);
    pr_info("mydriver: unloaded!\n");
}

module_init(mydriver_init);
module_exit(mydriver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("sehyeon");
MODULE_DESCRIPTION("ioctl driver");
