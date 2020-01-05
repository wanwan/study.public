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

IMG=helloos.img

LIBFLAGS=-L. -lc

IPLBIN=haribote/ipl.bin
KERNEL=haribote/kernel

APLSUBDIR=a hello3 hello4 winhelo winhelo2 winhelo3 star1 stars stars2 lines walk noodle beepdown color color2 sosu sosu2 sosu3 type iroha chklang notrec bball invader calc tview mmlplay


.PHONY: all libc apilib apl kernel makedisk install run clean

all: kernel libc apilib apl makedisk install makeiso

kernel:
	make -C haribote

libc:
	make -C libc

apilib: 
	make -C apilib

apl:
	for subdir in $(APLSUBDIR); do \
		make -C $$subdir; \
	done


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

makeiso:
	mkdir -p cdrootfs
	cp $(IMG) cdrootfs
	mkisofs -b helloos.img -r -J -o cdrom.img ./cdrootfs

install: kernel makedisk apl
	mkdir -p mnt
	sudo mount -o rw,loop $(IMG) ./mnt
	sudo cp $(KERNEL) ./mnt
	echo "hello world" > hello.txt
	echo "	this is a tab1" >> hello.txt
	echo "	this is a tab2" >> hello.txt
	echo "		this is a tabtab" >> hello.txt
	sudo cp hello.txt ./mnt
	sudo cp a/a.hrb ./mnt
	sudo cp hello3/hello3.hrb ./mnt
	sudo cp hello4/hello4.hrb ./mnt
	sudo cp winhelo/winhelo.hrb ./mnt
	sudo cp winhelo2/winhelo2.hrb ./mnt
	sudo cp winhelo3/winhelo3.hrb ./mnt
	sudo cp star1/star1.hrb ./mnt
	sudo cp stars/stars.hrb ./mnt
	sudo cp stars2/stars2.hrb ./mnt
	sudo cp lines/lines.hrb ./mnt
	sudo cp walk/walk.hrb ./mnt
	sudo cp noodle/noodle.hrb ./mnt
	sudo cp beepdown/beepdown.hrb ./mnt
	sudo cp color/color.hrb ./mnt
	sudo cp color2/color2.hrb ./mnt
	sudo cp sosu/sosu.hrb ./mnt
	sudo cp sosu2/sosu2.hrb ./mnt
	sudo cp sosu3/sosu3.hrb ./mnt
	sudo cp typeipl/typeipl.hrb ./mnt
	sudo cp ipl10.nas ./mnt
	sudo cp type/type.hrb ./mnt
	sudo cp iroha/iroha.hrb ./mnt
#	sudo cp nihongo/nihongo.fnt ./mnt
	sudo cp nihongo.compressed/nihongo.fnt ./mnt
	sudo cp chklang/chklang.hrb ./mnt
	sudo cp euc.txt ./mnt
	sudo cp notrec/notrec.hrb ./mnt
	sudo cp bball/bball.hrb ./mnt
	sudo cp invader/invader.hrb ./mnt
	sudo cp calc/calc.hrb ./mnt
	sudo cp tview/tview.hrb ./mnt
	sudo cp mmlplay/mmlplay.hrb ./mnt
	sudo cp mmldata/*.mml ./mnt
	sudo umount ./mnt

run: all
	$(QEMU) -vga std -S -s -fda $(IMG) -serial stdio -soundhw pcspk -k us
#	$(QEMU) -vga std -S -s -fda $(IMG) -serial pty

runcd: all
	$(QEMU) -vga std -S -s -cdrom cdrom.img -serial stdio -soundhw pcspk -k us

clean:
	rm -f *.a *.o *~ *.bin *.img *.elf *.hrb $(KERNEL)
	make cleanapl
	make -C apilib clean
	make -C libc clean

cleanapl: 
	for subdir in $(APLSUBDIR); do \
		make -C $$subdir clean ; \
	done
