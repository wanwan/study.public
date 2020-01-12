// cf. https://osdev-jp.readthedocs.io/ja/latest/2017/create-uefi-app-with-edk2.html

#include  <Uefi.h>
#include  <Library/UefiLib.h>

EFI_STATUS
EFIAPI
UefiMain (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
    )
{
  Print(L"Hello EDK II.\n");
  while (1);
  return 0;
}
