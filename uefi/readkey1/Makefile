SRCS=readkey.c
OBJS=readkey.o
LLVM_CC=clang
LLVM_LLD_LINK=lld-link
CFLAGS_LOADER=-target x86_64-pc-win32-coff \
	   -fno-stack-protector -fno-exceptions -fshort-wchar \
	   -mno-red-zone \
	   -nostdlibinc \
	   -Ithird_party_root/include

.PHONY: default

default: $(OBJS)
	$(LLVM_LLD_LINK) \
		-subsystem:efi_application -nodefaultlib \
		-entry:efi_main $(OBJS) -out:BOOTX64.EFI


.c.o:
	$(LLVM_CC) -c -o $@ $< $(CFLAGS_LOADER)
