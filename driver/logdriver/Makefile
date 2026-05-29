KERNEL_DIR ?= /embedded-linux-qemu-labs/kernel/linux
ARCH := arm
CROSS_COMPILE := arm-linux-gnueabihf-

obj-m := logdriver.o

all:
	make -C $(KERNEL_DIR) \
		ARCH=$(ARCH) \
		CROSS_COMPILE=$(CROSS_COMPILE) \
		M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) \
		ARCH=$(ARCH) \
		CROSS_COMPILE=$(CROSS_COMPILE) \
		M=$(PWD) clean
