SECTIONS
{
  . = 0x280000;
  .text : { *(.text) }
  .data : { *(.data) }
  .bss : { *(.bss) }
}
