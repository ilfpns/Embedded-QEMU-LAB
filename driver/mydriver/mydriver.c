#include <linux/module.h>    // 모듈 필수 헤더
#include <linux/fs.h>        // file_operations
#include <linux/cdev.h>      // cdev 구조체
#include <linux/uaccess.h>   // copy_to_user, copy_from_user

#define DRIVER_NAME "mydriver"
#define MSG "Hello from kernel driver!\n"

static int major;            // 디바이스 번호 (커널이 자동 할당)
static struct cdev my_cdev;  // 캐릭터 디바이스 구조체

/* read() 시스템콜 → 이 함수 호출 */
static ssize_t my_read(struct file *file, char __user *buf,
                       size_t count, loff_t *ppos)
{
    int len = strlen(MSG);

    if (*ppos >= len)        // 이미 다 읽었으면 0 반환
        return 0;

    if (copy_to_user(buf, MSG, len)) // 커널→유저 공간 복사
        return -EFAULT;

    *ppos += len;
    pr_info("mydriver: read() called\n");  // 커널 로그 출력
    return len;
}

/* write() 시스템콜 → 이 함수 호출 */
static ssize_t my_write(struct file *file, const char __user *buf,
                        size_t count, loff_t *ppos)
{
    char kbuf[128] = {0};
    int len = min(count, sizeof(kbuf) - 1);

    if (copy_from_user(kbuf, buf, len))  // 유저→커널 공간 복사
        return -EFAULT;

    pr_info("mydriver: write() received: %s\n", kbuf);  // 커널 로그
    return count;
}

/* open() 시스템콜 → 이 함수 호출 */
static int my_open(struct inode *inode, struct file *file)
{
    pr_info("mydriver: open() called\n");
    return 0;
}

/* close() 시스템콜 → 이 함수 호출 */
static int my_release(struct inode *inode, struct file *file)
{
    pr_info("mydriver: release() called\n");
    return 0;
}

/* 시스템콜 → 함수 매핑 테이블 */
static const struct file_operations my_fops = {
    .owner   = THIS_MODULE,
    .read    = my_read,
    .write   = my_write,
    .open    = my_open,
    .release = my_release,
};

/* insmod 시 실행 */
static int __init mydriver_init(void)
{
    dev_t dev;

    // 디바이스 번호 자동 할당
    alloc_chrdev_region(&dev, 0, 1, DRIVER_NAME);
    major = MAJOR(dev);

    // cdev 초기화 및 등록
    cdev_init(&my_cdev, &my_fops);
    cdev_add(&my_cdev, dev, 1);

    pr_info("mydriver: loaded! major=%d\n", major);
    pr_info("mydriver: run: mknod /dev/mydriver c %d 0\n", major);
    return 0;
}

/* rmmod 시 실행 */
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
MODULE_DESCRIPTION("Simple character device driver");
