CROSS=
AS=${CROSS}as
LD=${CROSS}ld
CC=${CROSS}gcc
STRIP=strip
#CFLAGS=-m32 -Wl,--build-id=none
CFLAGS=-c 
LDFLAGS=-s -static
IPLLDS=-T ipl.lds
KERNELLDS=-T kernel.lds
OBJCOPY=objcopy
QEMU=qemu-system-x86_64

IPLSRC=ipl.S
IPLOBJ=ipl.o
IPLELF=ipl.elf
IPLBIN=ipl.bin

IMG=helloos.img

KERNELSRC=asmhead.S
KERNELOBJ=asmhead.o
KERNELELF=asmhead.elf
KERNEL=kernel

all: ipl kernel makedisk install

ipl: $(IPLSRC)
	${CC} $(CFLAGS) -o $(IPLOBJ) $(IPLSRC)
	${LD} $(IPLOBJ) -o $(IPLELF) $(LDFLAGS) $(IPLLDS)
	$(STRIP) --remove-section=.note.gnu.property $(IPLELF)
	$(OBJCOPY) -O binary $(IPLELF) $(IPLBIN)

kernel: $(KERNELSRC)
	$(CC) $(CFLAGS) -o $(KERNELOBJ) $(KERNELSRC)
	${LD} $(KERNELOBJ) -o $(KERNELELF) $(LDFLAGS) $(KERNELLDS)
	${OBJCOPY} -O binary $(KERNELELF) $(KERNEL)

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

run:
	qemu-system-x86_64 -fda $(IMG) -s

run-debug:
	qemu-system-x86_64 -fda $(IMG) -s -S

clean:
	rm -f *.o *~ *.bin *.img *.elf $(KERNEL)
