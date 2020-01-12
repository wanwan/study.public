
#include "efi.h"

EFI_HANDLE          image_handle;
EFI_SYSTEM_TABLE    *system_table;

CHAR16              *hello_str = (CHAR16 *)L"Hello, you slab of warm meat!\r\n";

void efi_main(void* image_handle, EFI_SYSTEM_TABLE* system_table) {

//    image_handle = ih;
//    system_table = st;
    system_table->ConOut->OutputString(system_table->ConOut, hello_str);
    while (1);
}

