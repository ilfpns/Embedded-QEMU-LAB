#ifndef MYDRIVER_H
#define MYDRIVER_H

#include <linux/ioctl.h>

/* magic number - 다른 드라이버와 충돌 방지용 */
#define MYDRV_MAGIC 'M'

/* ioctl 명령어 정의 */
#define MYDRV_IOCTL_SET_VALUE  _IOW(MYDRV_MAGIC, 1, int)  /* 값 설정 */
#define MYDRV_IOCTL_GET_VALUE  _IOR(MYDRV_MAGIC, 2, int)  /* 값 읽기 */
#define MYDRV_IOCTL_RESET      _IO(MYDRV_MAGIC,  3)        /* 초기화 */

#endif
