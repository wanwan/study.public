CROSS=
AS=${CROSS}as
LD=${CROSS}ld
CC=${CROSS}gcc
#CFLAGS=-m32 -Wl,--build-id=none
CFLAGS=-c
KERNELCFLAGS=-c -m32 -Wl,--build-id=none
LDFLAGS=-s -static
IPLLDS=-T ipl.lds
KERNELLDS=-T kernel.lds -nostdlib
ASMHEADLDS=-T asmhead.lds
OBJCOPY=objcopy
QEMU=qemu-system-x86_64
STRIP=strip

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

all: ipl kernelhead font kernel makedisk install

ipl: $(IPLSRC)
	${CC} $(CFLAGS) -o $(IPLOBJ) $(IPLSRC)
	${LD} $(IPLOBJ) -o $(IPLELF) $(LDFLAGS) $(IPLLDS)
	$(STRIP) --remove-section=.note.gnu.property $(IPLELF)
	${OBJCOPY} -O binary $(IPLELF) $(IPLBIN)

kernelhead: $(KERNELHEADSRC)
	$(CC) $(CFLAGS) -o $(KERNELHEADOBJ) $(KERNELHEADSRC)
	${LD} $(KERNELHEADOBJ) -o $(KERNELHEADELF) $(LDFLAGS) $(ASMHEADLDS)
	$(STRIP) --remove-section=.note.gnu.property $(KERNELHEADELF)
	${OBJCOPY} -O binary $(KERNELHEADELF) $(KERNELHEADBIN)

naskfunc.o: naskfunc.S
	$(CC) $(KERNELCFLAGS) -o $@ $< -fno-pie -fno-asynchronous-unwind-tables

kernel: $(KERNELSRC) kernelhead naskfunc.o
	$(CC) $(KERNELCFLAGS) -o $(KERNELOBJ) $(KERNELSRC) -fno-pie -fno-asynchronous-unwind-tables
	${LD} $(KERNELOBJ) naskfunc.o font_8x16.o -o $(KERNELELF) -m elf_i386 $(LDFLAGS) $(KERNELLDS)
	$(STRIP) --remove-section=.note.gnu.property $(KERNELELF)
	${OBJCOPY} -O binary $(KERNELELF) $(KERNELBIN)
	cat $(KERNELHEADBIN) $(KERNELBIN) > $(KERNEL)

font:
	make -C fonts
	cp fonts/font_8x16.o .


makedisk:
	dd if=/dev/zero of=$(IMG) bs=512 count=2880
	mkfs.fat $(IMG)
	dd if=$(IPLBIN) of=$(IMG) conv=notrunc
#	dd if=/dev/urandom of=dummy.bin bs=512 count=1
#	dd if=dummy.bin of=$(IMG) bs=512 seek=1 count=1 conv=notrunc

install: kernel makedisk
	mkdir -p mnt
	sudo mount -o rw,loop $(IMG) ./mnt
	sudo cp $(KERNEL) ./mnt
	sudo umount ./mnt

run: all
	qemu-system-x86_64 -S -s -fda $(IMG)

clean:
	rm -f *.o *~ *.bin *.img *.elf $(KERNEL)
