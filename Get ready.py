import os
import sys
import re

out = False
if len(sys.argv) > 1:
    out = True

if out:
    print("Deleting old binary")
os.unlink("boot.bin")
if out:
    print("generating new binary")
os.system("nasm boot.asm -o boot.bin")
with open("boot.bin", "rb") as boot:
    bootdata = boot.read()

btf = 510 - len(bootdata)
if btf < 1:
    sys.stdout.flush()
    os.system("cls")
    print("Your code is too big for the MBR, please make it smaller")
    sys.stdout.flush()
    exit(1)
bootdata += bytes([0x00] * btf)
bootdata += bytes([0x55, 0xAA])
with open("bootpatched.bin", "wb") as patch:
    patch.write(bootdata)
bootbytes = []
for data in bootdata:
    bootbytes.append(data)
bootstr = f"{bootbytes}".replace("[", "{").replace("]", "}")
c_code = f"""unsigned char bootBytes[512] = {bootstr};"""
with open("main.c") as c_file:
    c_contents = c_file.read()
with open("main.c", "w") as write_file:
    write_file.write(
        re.sub(
            r"unsigned char bootBytes\[512] = \{.*?};", c_code, c_contents, 1, re.DOTALL
        )
    )
