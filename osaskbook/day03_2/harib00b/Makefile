CROSS=
AS=${CROSS}as
LD=${CROSS}ld
CC=${CROSS}gcc
#CFLAGS=-m32 -Wl,--build-id=none
CFLAGS=-nostdlib
LDFLAGS=-s -static -T ipl.lds 
OBJCOPY=objcopy
QEMU=qemu-system-x86_64

IPLSRC=ipl.S
IPLOBJ=ipl.o
IPLELF=ipl.elf
IPLBIN=ipl.bin

IMG=helloos.img


all: ipl makedisk

ipl: $(IPLSRC)
	${AS} ${CFLAGS} -o $(IPLOBJ) $(IPLSRC)
	${LD} $(IPLOBJ) -o $(IPLELF) ${LDFLAGS}
	${OBJCOPY} -O binary $(IPLELF) $(IPLBIN)

makedisk:
	dd if=/dev/zero of=$(IMG) bs=512 count=2880
	dd if=$(IPLBIN) of=$(IMG) conv=notrunc
	dd if=/dev/urandom of=dummy.bin bs=512 count=1
	dd if=dummy.bin of=$(IMG) bs=512 seek=1 count=1 conv=notrunc

run:
	qemu-system-x86_64 -fda $(IMG) -s

clean:
	rm -f *.o *~ *.bin *.img *.elf
