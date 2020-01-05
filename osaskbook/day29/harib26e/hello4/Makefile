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
APLCFLAGS=-m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -fno-stack-protector -nostdlib -I../

APLLIBFLAGS=-L../apilib -lapi -L../libc -lc


.PHONY: hello4

all: hello4

hello4: hello4.c
	$(CC) -c $(APLCFLAGS) hello4.c -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 -o hello4.o
	$(CC) -m32 -static -Wl,-eHariMain -Wl,--build-id=none -nostdlib -o hello4.elf hello4.o $(APLLIBFLAGS)
	$(CC) -m32 -static -Wl,-eHariMain -Wl,--build-id=none -nostdlib $(APLLDSCRIPT) -o hello4.hrb hello4.o $(APLLIBFLAGS)
	${OBJCOPY} -O binary hello4.elf hello4.bin

.c.o:
	$(CC) $(CFLAGS) $<

.S.o:
	$(CC) -c $<

clean:
	rm -f *.a *.o *~ *.bin *.img *.elf *.hrb $(KERNEL)
