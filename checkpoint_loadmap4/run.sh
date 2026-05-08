#!/bin/bash

KERNEL_ADDR=0x62000000
DTB_ADDR=0x68000000
ROOTFS_ADDR=0x69000000

KERNEL=../kernel/linux/arch/arm/boot/zImage
DTB=../kernel/linux/arch/arm/boot/dts/arm/vexpress-v2p-ca9.dtb
ROOTFS=/embedded-linux-qemu-labs/rootfs.cpio.uboot

qemu-system-arm \
  -M vexpress-a9 \
  -m 256M \
  -kernel u-boot \
  -device loader,file=${KERNEL},addr=${KERNEL_ADDR} \
  -device loader,file=${DTB},addr=${DTB_ADDR} \
  -device loader,file=${ROOTFS},addr=${ROOTFS_ADDR} \
  -nographic \
  -audio none
