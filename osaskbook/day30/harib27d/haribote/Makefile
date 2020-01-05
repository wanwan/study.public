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

IPLSRC=ipl.S
IPLOBJ=ipl.o
IPLELF=ipl.elf
IPLBIN=ipl.bin

IMG=helloos.img

KERNELHEADSRC=asmhead.S
KERNELHEADOBJ=asmhead.o
KERNELHEADELF=asmhead.elf
KERNELHEADBIN=asmhead.bin

KERNELSRC=bootpack.c
KERNELOBJ=bootpack.o
KERNELBIN=kernel.bin
KERNELELF=kernel.elf
KERNEL=kernel

APLLIBSRC=a_nask.S
APLLIBOBJ=a_nask.o
APLLIB=libapl.a
APLLIBFLAGS=-L. -lapl

LIBFLAGS=-L. -lc

KERNELOBJS=bootpack.o dsctbl.o graphics.o int.o fifo.o mouse.o keyboard.o memory.o sheet.o timer.o mtask.o file.o window.o console.o tek.o

.PHONY: all ipl kernelhead kernel libc font 

#all: ipl kernelhead libc font apl kernel makedisk install
all: ipl kernelhead libc font kernel

ipl: $(IPLOBJ)
	${LD} $(IPLOBJ) -o $(IPLELF) $(LDFLAGS) $(IPLLDS)
	$(STRIP) --remove-section=.note.gnu.property $(IPLELF)
	${OBJCOPY} -O binary $(IPLELF) $(IPLBIN)

kernelhead: $(KERNELHEADOBJ)
	${LD} $(KERNELHEADOBJ) -o $(KERNELHEADELF) $(LDFLAGS) $(ASMHEADLDS)
	$(STRIP) --remove-section=.note.gnu.property $(KERNELHEADELF)
	${OBJCOPY} -O binary $(KERNELHEADELF) $(KERNELHEADBIN)

naskfunc.o: naskfunc.S
	$(CC) $(KERNELCFLAGS) $< -c -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0

kernel: $(KERNELOBJS) kernelhead naskfunc.o
	${LD} $(KERNELOBJS) naskfunc.o font_8x16.o hankaku.o -o $(KERNELELF) -m elf_i386 $(LDFLAGS) $(KERNELLDS) -Llibc -lc
	$(STRIP) --remove-section=.note.gnu.property $(KERNELELF)
	${OBJCOPY} -O binary $(KERNELELF) $(KERNELBIN)
	cat $(KERNELHEADBIN) $(KERNELBIN) > $(KERNEL)

libc:
	make -C libc
	cp libc/libc.a .

font:
	make -C fonts
	cp fonts/font_8x16.o .
	cp fonts/hankaku.o .

.c.o:
	$(CC) $(CFLAGS) $<

.S.o:
	$(CC) -c $<


run: all
	$(QEMU) -vga std -S -s -fda $(IMG) -serial stdio -soundhw pcspk
#	$(QEMU) -vga std -S -s -fda $(IMG) -serial pty

clean:
	rm -f *.a *.o *~ *.bin *.img *.elf *.hrb $(KERNEL)
	make -C libc clean
	make -C fonts clean
