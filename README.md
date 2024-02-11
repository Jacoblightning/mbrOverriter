# mbrOverriter
A simple MBR overriter (for windows) written in C
# Building
If you changed boot.asm, remake main.c with get ready.py:
```shell
# Edit boot.asm
nano boot.asm
# Remake main.c
python "get ready.py"
# Compile
cl main.c
```
#### You can also compile with tcc
# Testing Safely
## You can use qemu to test it:
```shell
qemu-system-x86_64.exe -hda bootpatched.bin
```
## You can also test it on [anyrun](https://any.run)
https://app.any.run/tasks/794acb0f-ce84-47d6-8af9-bca9c8c69f33/
# What is does:
## 1. 
### If debug mode is on, it will display a warning.
## 2.
### It will check if it was run as administrator.
## 3.
### Open `\\\\.\\PhysicalDrive0` (where the mbr is stored)
## 4.
### Write the boot file to the mbr
#### (The boot file is inlined with `get ready.py`. It is not needed to run.)
## 5.
### Bluescreen the computer
# For the future
## Nothing right non but I will try to fix any issues.