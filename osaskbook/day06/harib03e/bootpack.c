#include <stdio.h>
#include "bootpack.h"


void HariMain(void)
{
	struct BOOTINFO *binfo;
	char s[40], mcursor[256];
	int mx, my;
	
	binfo = (struct BOOTINFO *) ADR_BOOTINFO;

	init_gdtidt();
	init_pic();
	_io_sti(); /* IDT/PICの初期化が終わったのでCPUの割り込み禁止を解除 */
	
	init_palette();
	init_screen8((char *)binfo->vram, binfo->scrnx, binfo->scrny);

	mx = (binfo->scrnx - 16) / 2; /* 画面中央になるように座標計算 */
	my = (binfo->scrny - 28 - 16) / 2;
	init_mouse_cursor8(mcursor, COL8_008484);
	//putblock8_8((char *)binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);
	//sprintf(s, "(%d, %d)", mx, my);
	//putfonts8_asc((char *)binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);

	_io_out8(PIC0_IMR, 0xf9); /* PIC1とキーボードを許可(11111001) */
	_io_out8(PIC1_IMR, 0xef); /* マウスを許可(11101111) */

	//_io_out8(PIC0_IMR, 0xfa); /* PIC1 の入力を許可 (11111011) */
	//_io_out8(PIC1_IMR, 0xef); /* マウスを許可(11101111) */

		
	for (;;) {
		_io_hlt();
	}
}


