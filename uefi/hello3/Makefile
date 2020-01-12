LLVM_CC=clang
LLVM_LLD_LINK=lld-link
CFLAGS_LOADER=-target x86_64-pc-win32-coff \
	   -fno-stack-protector -fno-exceptions -fshort-wchar \
	   -mno-red-zone \
	   -nostdlibinc \
	   -Ithird_party_root/include

.PHONY: default

default:
	$(LLVM_CC) -c -o hello3.o hello3.c $(CFLAGS_LOADER)
	$(LLVM_LLD_LINK) \
		-subsystem:efi_application -nodefaultlib \
		-entry:efi_main hello3.o -out:BOOTX64.EFI
