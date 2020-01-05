CROSS=
AS=${CROSS}as
LD=${CROSS}ld
CC=${CROSS}gcc
#CFLAGS=-m32 -Wl,--build-id=none
CFLAGS=-c -m32 -Wl,--build-id=none
KERNELCFLAGS=-c -m32 -Wl,--build-id=none
LDFLAGS=-s -static
IPLLDS=-T ipl.lds
KERNELLDS=-T kernel.lds -nostdlib
ASMHEADLDS=-T asmhead.lds
OBJCOPY=objcopy
QEMU=qemu-system-x86_64
STRIP=strip

FONTFILESRC=font_8x16.c hankaku.c
FONTFILEOBJ=font_8x16.o hankaku.o

all: font

font:$(FONTFILEOBJ) 

.c.o:
	${CC} $(CFLAGS) -o $@ $<


clean:
	rm -f *.o *~ *.bin *.img *.elf $(KERNEL)
