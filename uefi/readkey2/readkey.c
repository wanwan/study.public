
#include "efi.h"

EFI_HANDLE          image_handle;
EFI_SYSTEM_TABLE    *system_table;

CHAR16              *hello_str = (CHAR16 *)L"Hello, you slab of warm meat!\r\n";

void efi_main(void* image_handle, EFI_SYSTEM_TABLE* system_table) {

    EFI_INPUT_KEY key;
    unsigned short str[3];

    system_table->ConOut->ClearScreen(system_table->ConOut);
    while (1) {
	if (!system_table->ConIn->ReadKeyStroke(system_table->ConIn, &key)) {
	    if (key.UnicodeChar != L'\r') {
		str[0] = key.UnicodeChar;
		str[1] = L'\0';		
	    }
	    else {
		str[0] = L'\r';
		str[1] = L'\n';
		str[2] = L'\0';		
	    }
	    system_table->ConOut->OutputString(system_table->ConOut, str);
	}
    }

    
//    image_handle = ih;
//    system_table = st;
//    system_table->ConOut->OutputString(system_table->ConOut, hello_str);
    while (1);
}

