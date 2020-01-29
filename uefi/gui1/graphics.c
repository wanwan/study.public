#include "efi.h"
#include "graphics.h"

extern EFI_GRAPHICS_OUTPUT_PROTOCOL *graphics_output;
const EFI_GRAPHICS_OUTPUT_BLT_PIXEL white = {0xff, 0xff, 0xff, 0xff};
const EFI_GRAPHICS_OUTPUT_BLT_PIXEL red = {0xff, 0x00, 0x00, 0xff};
const EFI_GRAPHICS_OUTPUT_BLT_PIXEL green = {0x00, 0xff, 0x00, 0xff};
const EFI_GRAPHICS_OUTPUT_BLT_PIXEL blue = {0x00, 0x00, 0xff, 0xff};

void draw_pixel(unsigned int x, unsigned int y,
		EFI_GRAPHICS_OUTPUT_BLT_PIXEL color)
{
	unsigned int hr = graphics_output->Mode->Info->HorizontalResolution;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *base =
		(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)graphics_output->Mode->FrameBufferBase;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *p = base + (hr * y) + x;

	p->Blue = color.Blue;
	p->Green = color.Green;
	p->Red = color.Red;
	p->Reserved = color.Reserved;
}


void draw_rect(RECT r, EFI_GRAPHICS_OUTPUT_BLT_PIXEL c)
{
	unsigned int i;

	for (i = r.x; i < (r.x + r.w); i++)
		draw_pixel(i, r.y, c);
	for (i = r.x; i < (r.x + r.w); i++)
		draw_pixel(i, r.y + r.h - 1, c);

	for (i = r.y; i < (r.y + r.h); i++)
		draw_pixel(r.x, i, c);
	for (i = r.y; i < (r.y + r.h); i++)
		draw_pixel(r.x + r.w - 1, i, c);
}
