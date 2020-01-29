
#include "efi.h"
#include "common.h"
#include "shell.h"

EFI_HANDLE          image_handle;
EFI_SYSTEM_TABLE    *system_table;
EFI_GRAPHICS_OUTPUT_PROTOCOL *graphics_output;

CHAR16              *hello_str = (CHAR16 *)L"Hello, you slab of warm meat!\r\n";

void efi_main(void* image_handle, EFI_SYSTEM_TABLE* _system_table) {

    EFI_INPUT_KEY key;
    unsigned short str[3];

    EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    
    system_table = _system_table;

    system_table->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
    system_table->BootServices->LocateProtocol(&gop_guid, NULL, (void **)&graphics_output);
    
    system_table->ConOut->ClearScreen(system_table->ConOut);

    shell();

}

