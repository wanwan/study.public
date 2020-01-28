#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "efi.h"

typedef struct _RECT {
	unsigned int x, y;
	unsigned int w, h;
} RECT;

extern const EFI_GRAPHICS_OUTPUT_BLT_PIXEL white;


void draw_pixel(unsigned int x, unsigned int y,
		EFI_GRAPHICS_OUTPUT_BLT_PIXEL color);
void draw_rect(RECT r, EFI_GRAPHICS_OUTPUT_BLT_PIXEL c);

#endif /* __GRAPHICS_H__ */
