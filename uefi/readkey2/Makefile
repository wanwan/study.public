QEMU=qemu-system-x86_64
UEFI_CODE=-drive if=pflash,format=raw,readonly,file=uefi_bios.x64/OVMF_CODE.fd
UEFI_FLASH=-drive if=pflash,format=raw,file=uefi_bios.x64/OVMF_VARS.fd

SRCS=readkey.c common.c shell.c
OBJS=readkey.o common.o shell.o
LLVM_CC=clang
LLVM_LLD_VER=-6.0
LLVM_LLD_LINK=lld-link$(LLVM_LLD_VER)
CFLAGS_LOADER=-target x86_64-pc-win32-coff \
	   -fno-stack-protector -fno-exceptions -fshort-wchar \
	   -mno-red-zone \
	   -nostdlibinc \
	   -Ithird_party_root/include

.PHONY: default install run

default: $(OBJS)
	$(LLVM_LLD_LINK) \
		-subsystem:efi_application -nodefaultlib \
		-entry:efi_main $(OBJS) -out:BOOTX64.EFI

install: default
	mkdir -p efi.image/efi/boot/
	cp BOOTX64.EFI efi.image/efi/boot/

run: install
	$(QEMU) $(UEFI_CODE) $(UEFI_FLASH) -hda fat:rw:efi.image/ -net none

$(OBJS):$(SRCS)

.c.o:
	$(LLVM_CC) -c -o $@ $< $(CFLAGS_LOADER)


