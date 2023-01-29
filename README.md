# An Operating System

Mostly incomplete


An operating system I am currently working on because I want to learn about how operating systems work. It will run on Intel chips.  I have learned about linkerscript, interrupts, faults, paging, BIOS and more. It boots itself up into VGA mode using GRUB. It can handle keyboard inputs, faults, exceptions, and traps, and it can display text and colors in VGA mode.  I’m using EMU as my virtual machine and remote GDB as my debugger.  Working on paging and entering x64 bit mode. Roughly following various tutorials from http://www.osdever.net/ and using OS Dev Wiki and Intel documentation. 

If you want to compile it yourself, run `build.sh.`
Then run `run.sh`
If you want to debug, use `debug.sh`
