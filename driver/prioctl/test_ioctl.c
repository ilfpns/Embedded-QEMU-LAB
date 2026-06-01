#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "myioctl.h"

int main()
{
    int fd, val;

    fd = open("/dev/mydriver", O_RDWR);
    if (fd < 0) {
        perror("open failed");
        return 1;
    }
    printf("opened /dev/mydriver\n");

    /* SET_VALUE 테스트 */
    val = 42;
    ioctl(fd, MYDRV_IOCTL_SET_VALUE, &val);
    printf("SET_VALUE: %d\n", val);

    /* GET_VALUE 테스트 */
    val = 0;
    ioctl(fd, MYDRV_IOCTL_GET_VALUE, &val);
    printf("GET_VALUE: %d\n", val);

    /* RESET 테스트 */
    ioctl(fd, MYDRV_IOCTL_RESET, 0);
    printf("RESET done\n");

    /* RESET 후 GET_VALUE */
    ioctl(fd, MYDRV_IOCTL_GET_VALUE, &val);
    printf("GET_VALUE after RESET: %d\n", val);

    close(fd);
    return 0;
}
