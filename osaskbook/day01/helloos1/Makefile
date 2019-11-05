all:
	gcc -m32 -Wl,--build-id=none -o helloos.elf helloos.S -s -nostartfiles -nostdlib -static 
	objcopy -O binary helloos.elf helloos.bin
	dd if=/dev/zero of=helloos.img bs=512 count=2880
	dd if=helloos.bin of=helloos.img conv=notrunc

run:
	qemu-system-x86_64 -fda ./helloos.bin
