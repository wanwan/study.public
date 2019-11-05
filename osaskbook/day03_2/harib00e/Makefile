CROSS=
AS=${CROSS}as
LD=${CROSS}ld
CC=${CROSS}gcc
#CFLAGS=-m32 -Wl,--build-id=none
CFLAGS=-c 
LDFLAGS=-s -static -T ipl.lds 
OBJCOPY=objcopy
QEMU=qemu-system-x86_64
STRIP=strip

IPLSRC=ipl.S
IPLOBJ=ipl.o
IPLELF=ipl.elf
IPLBIN=ipl.bin

IMG=helloos.img

KERNELSRC=haribote.S
KERNELOBJ=haribote.o
KERNELELF=haribote.elf
KERNEL=haribote

MOUNTDIR=mnt/osask


all: ipl kernel makedisk install

ipl: $(IPLSRC)
	${CC} $(CFLAGS) -o $(IPLOBJ) $(IPLSRC)
	${LD} $(IPLOBJ) -o $(IPLELF) ${LDFLAGS}
	$(STRIP) --remove-section=.note.gnu.property $(IPLELF)
	${OBJCOPY} -O binary $(IPLELF) $(IPLBIN)

kernel: $(KERNELSRC)
	$(CC) $(CFLAGS) -o $(KERNELOBJ) $(KERNELSRC)
	${LD} $(KERNELOBJ) -o $(KERNELELF) ${LDFLAGS}
	$(STRIP) --remove-section=.note.gnu.property $(KERNELELF)
	${OBJCOPY} -O binary $(KERNELELF) $(KERNEL)

makedisk:
	dd if=/dev/zero of=$(IMG) bs=512 count=2880
	mkfs.fat $(IMG)
	dd if=$(IPLBIN) of=$(IMG) conv=notrunc
#	dd if=/dev/urandom of=dummy.bin bs=512 count=1
#	dd if=dummy.bin of=$(IMG) bs=512 seek=1 count=1 conv=notrunc

install: kernel makedisk
	mkdir -p $(MOUNTDIR)
	sudo mount -o rw,loop $(IMG) $(MOUNTDIR)
	sudo cp $(KERNEL) $(MOUNTDIR)
	sudo umount $(MOUNTDIR)

run: all
	qemu-system-x86_64 -fda $(IMG) -s

clean:
	rm -f *.o *~ *.bin *.img *.elf $(KERNEL)
