CROSS=
AS=${CROSS}as
LD=${CROSS}ld
CC=${CROSS}gcc
#CFLAGS=-c -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -fno-stack-protector -O0
CFLAGS=-c -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -fno-stack-protector
#KERNELCFLAGS=-c -m32 -Wl,--build-id=none -O0
KERNELCFLAGS=-c -m32 -Wl,--build-id=none
LDFLAGS=-s -static
IPLLDS=-T ipl.lds
KERNELLDS=-T kernel.lds -nostdlib -Map=kernel.map
ASMHEADLDS=-T asmhead.lds
OBJCOPY=objcopy
QEMU=qemu-system-i386
#QEMU=qemu-system-x86_64
STRIP=strip

APLLDSCRIPT=-T ../haribote.lds
APLCFLAGS=-m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -fno-stack-protector -nostdlib

APLLIBFLAGS=-L../apilib -lapi


.PHONY: hello3

all: hello3


hello3: hello3.c
	$(CC) -c $(APLCFLAGS) hello3.c -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 -o hello3.o
	$(CC) -m32 -static -Wl,-eHariMain -Wl,--build-id=none -nostdlib -o hello3.elf hello3.o $(APLLIBFLAGS)
	$(CC) -m32 -static -Wl,-eHariMain -Wl,--build-id=none -nostdlib $(APLLDSCRIPT) -o hello3.hrb hello3.o $(APLLIBFLAGS)
	${OBJCOPY} -O binary hello3.elf hello3.bin


.c.o:
	$(CC) $(CFLAGS) $<

.S.o:
	$(CC) -c $<

clean:
	rm -f *.a *.o *~ *.bin *.img *.elf *.hrb $(KERNEL)
