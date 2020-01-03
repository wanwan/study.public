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

APLCFLAGS=-m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -fno-stack-protector -nostdlib


APILIBSRC=a_nask.S
APILIBOBJ=a_nask.o
APILIB=libapi.a
APILIBFLAGS=-L. -lapi

LIBFLAGS=-L. -lc


.PHONY: all 

all: apilib


a_nask.o: a_nask.S
	$(CC) -c $(APLCFLAGS) $< -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -nostdlib -O0


apilib: $(APILIBOBJ)
	$(AR) rcs $(APILIB) $(APILIBOBJ)

clean:
	rm -f *.a *.o *~ *.bin *.img *.elf *.hrb $(KERNEL)

