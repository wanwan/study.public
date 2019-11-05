CROSS=
AS=${CROSS}as
LD=${CROSS}ld
CC=${CROSS}gcc
#CFLAGS=-m32 -Wl,--build-id=none
CFLAGS=-nostdlib
LDFLAGS=-s -static -T ipl.lds 
OBJCOPY=objcopy
QEMU=qemu-system-x86_64

all:
	${AS} ${CFLAGS} -o helloos.o helloos.S 
	${LD} helloos.o -o helloos.elf ${LDFLAGS}
	${OBJCOPY} -O binary helloos.elf helloos.bin
	dd if=/dev/zero of=helloos.img bs=512 count=2880
	dd if=helloos.bin of=helloos.img conv=notrunc

run:
	qemu-system-x86_64 -fda ./helloos.bin

clean:
	rm -f *.o *~ *.bin *.img *.elf
