#!/bin/bash

CFLAGS="-m32 -fno-pie -c -fstrength-reduce -fomit-frame-pointer \
        -finline-functions  -ffreestanding -g   -c ../mainc.h ../idt.h ../clock.h ../cursor.h ../stdos.h ../page.h"
mkdir -p output/isodir/boot/grub

nasm -f elf32 -g -o output/main.o main.asm
cd output
gcc ${CFLAGS} ../mainc.c
gcc ${CFLAGS}  ../gdt.c 
gcc ${CFLAGS}  ../idt.c 
gcc ${CFLAGS}  ../keyboard.c 
gcc ${CFLAGS}  ../stdos.c 
gcc ${CFLAGS}  ../cursor.c 
gcc ${CFLAGS}  ../syscalls.c
gcc ${CFLAGS}  ../clock.c
gcc ${CFLAGS}  ../page.c
ld -m elf_i386 --oformat binary -T ../linkerscript.ld -o kernel.bin page.o mainc.o main.o gdt.o idt.o keyboard.o stdos.o cursor.o syscalls.o clock.o
ld -m elf_i386 -T ../linkerscript.ld -o symbtable page.o mainc.o main.o gdt.o idt.o keyboard.o stdos.o cursor.o syscalls.o clock.o

cd ..
cp output/kernel.bin output/isodir/boot/
cp grub/menu.lst output/isodir/boot/grub/
cp grub/stage2_eltorito output/isodir/boot/grub/
cd output
mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -quiet          \
  -input-charset utf8                                                 \
  -boot-load-size 4 -boot-info-table -o kernel.iso isodir 
