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

KERNELOBJS=bootpack.o dsctbl.o graphics.o int.o fifo.o mouse.o keyboard.o memory.o sheet.o timer.o mtask.o file.o window.o console.o

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
	${LD} $(KERNELOBJS) naskfunc.o font_8x16.o -o $(KERNELELF) -m elf_i386 $(LDFLAGS) $(KERNELLDS) -Llibc -lc
	$(STRIP) --remove-section=.note.gnu.property $(KERNELELF)
	${OBJCOPY} -O binary $(KERNELELF) $(KERNELBIN)
	cat $(KERNELHEADBIN) $(KERNELBIN) > $(KERNEL)

libc:
	make -C libc
	cp libc/libc.a .

font:
	make -C fonts
	cp fonts/font_8x16.o .

.c.o:
	$(CC) $(CFLAGS) $<

.S.o:
	$(CC) -c $<


makedisk:
	dd if=/dev/zero of=$(IMG) bs=512 count=2880
	mkfs.fat $(IMG)
	dd if=$(IPLBIN) of=$(IMG) conv=notrunc
#	dd if=/dev/urandom of=dummy.bin bs=512 count=1
#	dd if=dummy.bin of=$(IMG) bs=512 seek=1 count=1 conv=notrunc

install: kernel makedisk apl
	mkdir -p mnt
	sudo mount -o rw,loop $(IMG) ./mnt
	sudo cp $(KERNEL) ./mnt
	echo "hello world" > hello.txt
	echo "	this is a tab1" >> hello.txt
	echo "	this is a tab2" >> hello.txt
	echo "		this is a tabtab" >> hello.txt
	sudo cp hello.txt ./mnt
	sudo cp hello.hrb ./mnt
	sudo cp hello2.hrb ./mnt
	sudo cp a.hrb ./mnt
	sudo cp hello3.hrb ./mnt
	sudo cp crack1.hrb ./mnt
	sudo cp crack2.hrb ./mnt
	sudo cp crack3.hrb ./mnt
	sudo cp crack4.hrb ./mnt
	sudo cp bug1.hrb ./mnt
	sudo cp bug2.hrb ./mnt
	sudo cp bug3.hrb ./mnt
	sudo cp hello4.hrb ./mnt
	sudo cp winhelo.hrb ./mnt
	sudo cp winhelo2.hrb ./mnt
	sudo cp winhelo3.hrb ./mnt
	sudo cp star1.hrb ./mnt
	sudo cp stars.hrb ./mnt
	sudo cp stars2.hrb ./mnt
	sudo cp lines.hrb ./mnt
	sudo cp walk.hrb ./mnt
	sudo cp noodle.hrb ./mnt
	sudo cp beepdown.hrb ./mnt
	sudo cp color.hrb ./mnt
	sudo cp color2.hrb ./mnt
	sudo umount ./mnt

run: all
	$(QEMU) -vga std -S -s -fda $(IMG) -serial stdio -soundhw pcspk
#	$(QEMU) -vga std -S -s -fda $(IMG) -serial pty

clean:
	rm -f *.a *.o *~ *.bin *.img *.elf *.hrb $(KERNEL)
	make -C libc clean
	make -C fonts clean
