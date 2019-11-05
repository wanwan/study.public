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


all: ipl makedisk

ipl: $(IPLSRC)
	${AS} ${CFLAGS} -o $(IPLOBJ) $(IPLSRC)
	${LD} $(IPLOBJ) -o $(IPLELF) ${LDFLAGS}
	${OBJCOPY} -O binary $(IPLELF) $(IPLBIN)

makedisk:
	dd if=/dev/zero of=helloos.img bs=512 count=2880
	dd if=$(IPLBIN) of=helloos.img conv=notrunc

run:
	qemu-system-x86_64 -fda ./helloos.img

clean:
	rm -f *.o *~ *.bin *.img *.elf
