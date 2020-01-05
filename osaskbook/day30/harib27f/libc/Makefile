CROSS=
AS=${CROSS}as
LD=${CROSS}ld
AR=${CROSS}ar
CC=${CROSS}gcc
CFLAGS=-m32 -Wl,--build-id=none -nostdlib -fno-builtin -fno-stack-protector -fno-pie -fno-asynchronous-unwind-tables -c
KERNELCFLAGS=-c -m32 -Wl,--build-id=none
LDFLAGS=-s -static
IPLLDS=-T ipl.lds
KERNELLDS=-T kernel.lds -nostdlib
ASMHEADLDS=-T asmhead.lds
OBJCOPY=objcopy
QEMU=qemu-system-x86_64
STRIP=strip

SRCS=sprintf.c strcmp.c rand.c strlen.c strtol.c
OBJS=sprintf.o strcmp.o rand.o strlen.o strtol.o

all: libc

libc: $(OBJS)
	${AR} rcs libc.a $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o *~ *.a

