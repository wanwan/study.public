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

KERNELOBJS=bootpack.o dsctbl.o graphics.o int.o fifo.o mouse.o keyboard.o memory.o sheet.o timer.o mtask.o file.o window.o console.o

.PHONY: all ipl kernelhead kernel libc font apl makedisk install run clean

all: ipl kernelhead libc font apl kernel makedisk install

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


hello: hello.S
	$(CC) -c $(APLCFLAGS) $< -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 -o hello.elf
	${OBJCOPY} -O binary hello.elf hello.bin


hello2: hello2.S
	$(CC) -c $(APLCFLAGS) $< -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 -o hello2.elf
	${OBJCOPY} -O binary hello2.elf hello2.bin

a.bin: a.c a_nask.S
	$(CC) -c $(APLCFLAGS) a_nask.S -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 -o a_nask.o
	$(CC) -c $(APLCFLAGS) a.c -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 -o a.o
	$(CC) -m32 -static -Wl,-eHariMain -Wl,--build-id=none -nostdlib  -o a.elf a.o a_nask.o
	${OBJCOPY} -O binary a.elf a.bin


hello3: hello3.c a_nask.S
	$(CC) -c $(APLCFLAGS) a_nask.S -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 -o a_nask.o
	$(CC) -c $(APLCFLAGS) hello3.c -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 -o hello3.o
	$(CC) -m32 -static -Wl,-eHariMain -Wl,--build-id=none -nostdlib  -o hello3.elf hello3.o a_nask.o
	${OBJCOPY} -O binary hello3.elf hello3.bin


hello4: hello4.c a_nask.S
	$(CC) -c $(APLCFLAGS) a_nask.S -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 -o a_nask.o
	$(CC) -c $(APLCFLAGS) hello4.c -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 -o hello4.o
	$(CC) -m32 -static -Wl,-eHariMain -Wl,--build-id=none -nostdlib  -o hello4.elf hello4.o a_nask.o
	${OBJCOPY} -O binary hello4.elf hello4.bin


crack1: crack1.c a_nask.S
	$(CC) -c $(APLCFLAGS) a_nask.S -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 -o a_nask.o
	$(CC) -c $(APLCFLAGS) crack1.c -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 
	$(CC) -m32 -static -Wl,-eHariMain -Wl,--build-id=none -nostdlib  -o crack1.elf crack1.o a_nask.o
	${OBJCOPY} -O binary crack1.elf crack1.bin


crack2: crack2.S
	$(CC) -c $(APLCFLAGS) crack2.S -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 
	$(CC) -m32 -static -Wl,-eHariMain -Wl,--build-id=none -nostdlib  -o crack2.elf crack2.o
	${OBJCOPY} -O binary crack2.elf crack2.bin


crack3: crack3.S
	$(CC) -c $(APLCFLAGS) $< -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 -o crack3.elf
	${OBJCOPY} -O binary crack3.elf crack3.bin


crack4: crack4.S
	$(CC) -c $(APLCFLAGS) $< -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 -o crack4.elf
	${OBJCOPY} -O binary crack4.elf crack4.bin


bug1: bug1.c a_nask.S
	$(CC) -c $(APLCFLAGS) a_nask.S -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 -o a_nask.o
	$(CC) -c $(APLCFLAGS) bug1.c -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 
	$(CC) -m32 -static -Wl,-eHariMain -Wl,--build-id=none -nostdlib  -o bug1.elf bug1.o a_nask.o
	${OBJCOPY} -O binary bug1.elf bug1.bin


bug2: bug2.c a_nask.S
	$(CC) -c $(APLCFLAGS) a_nask.S -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 -o a_nask.o
	$(CC) -c $(APLCFLAGS) bug2.c -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 
	$(CC) -m32 -static -Wl,-eHariMain -Wl,--build-id=none -nostdlib  -o bug2.elf bug2.o a_nask.o
	${OBJCOPY} -O binary bug2.elf bug2.bin


bug3: bug3.c a_nask.S
	$(CC) -c $(APLCFLAGS) a_nask.S -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 -o a_nask.o
	$(CC) -c $(APLCFLAGS) bug3.c -m32 -Wl,--build-id=none -fno-pie -fno-asynchronous-unwind-tables -Ilibc/include -fno-builtin -O0 
	$(CC) -m32 -static -Wl,-eHariMain -Wl,--build-id=none -nostdlib  -o bug3.elf bug3.o a_nask.o
	${OBJCOPY} -O binary bug3.elf bug3.bin





apl: hello hello2 a.bin hello3 crack1 crack2 crack3 crack4 bug1 bug2 bug3 hello4

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
	sudo cp hello.bin ./mnt
	sudo cp hello2.bin ./mnt
	sudo cp a.bin ./mnt
	sudo cp hello3.bin ./mnt
	sudo cp crack1.bin ./mnt
	sudo cp crack2.bin ./mnt
	sudo cp crack3.bin ./mnt
	sudo cp crack4.bin ./mnt
	sudo cp bug1.bin ./mnt
	sudo cp bug2.bin ./mnt
	sudo cp bug3.bin ./mnt
	sudo cp hello4.bin ./mnt
	sudo umount ./mnt

run: all
	$(QEMU) -vga std -S -s -fda $(IMG)

clean:
	rm -f *.a *.o *~ *.bin *.img *.elf $(KERNEL)
	make -C libc clean
	make -C fonts clean
