CROSS=
AS=${CROSS}as
LD=${CROSS}ld
CC=${CROSS}gcc
#CFLAGS=-m32 -Wl,--build-id=none
#CFLAGS=-nostdlib
CFLAGS=-c
LDFLAGS=-s -static -T ipl.lds 
OBJCOPY=objcopy
STRIP=strip
QEMU=qemu-system-x86_64

IPLSRC=ipl.S
IPLOBJ=ipl.o
IPLELF=ipl.elf
IPLBIN=ipl.bin

IMG=helloos.img

# ダミーセクター数
#DISKDUMMYSIZE=17
DISKDUMMYSIZE=359   # 10x2x18 -1(MBR分)


all: ipl makedisk

ipl: $(IPLSRC)
#	${AS} ${CFLAGS} -o $(IPLOBJ) $(IPLSRC)
	${CC} ${CFLAGS} -o $(IPLOBJ) $(IPLSRC)
	${LD} $(IPLOBJ) -o $(IPLELF) ${LDFLAGS}
	$(STRIP) --remove-section=.note.gnu.property $(IPLELF)
	${OBJCOPY} -O binary $(IPLELF) $(IPLBIN)

makedisk: makedummysect
	dd if=/dev/zero of=$(IMG) bs=512 count=2880
	dd if=$(IPLBIN) of=$(IMG) conv=notrunc
	dd if=dummy.bin of=$(IMG) bs=512 seek=1 count=$(DISKDUMMYSIZE) conv=notrunc


makedummysect:
	dd if=/dev/urandom of=dummy.bin bs=512 count=$(DISKDUMMYSIZE)

run:
	qemu-system-x86_64 -fda $(IMG) -s

clean:
	rm -f *.o *~ *.bin *.img *.elf
