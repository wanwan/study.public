/* 割り込み関係 */

#include <stdio.h>
#include "bootpack.h"



void init_pic(void)
/* PICの初期化 */
{
	_io_out8(PIC0_IMR,  0xff  ); /* 全ての割り込みを受け付けない */
	_io_out8(PIC1_IMR,  0xff  ); /* 全ての割り込みを受け付けない */

	_io_out8(PIC0_ICW1, 0x11  ); /* エッジトリガモード */
	_io_out8(PIC0_ICW2, 0x20  ); /* IRQ0-7は、INT20-27で受ける */
	_io_out8(PIC0_ICW3, 1 << 2); /* PIC1はIRQ2にて接続 */
	_io_out8(PIC0_ICW4, 0x01  ); /* ノンバッファモード */

	_io_out8(PIC1_ICW1, 0x11  ); /* エッジトリガモード */
	_io_out8(PIC1_ICW2, 0x28  ); /* IRQ8-15は、INT28-2fで受ける */
	_io_out8(PIC1_ICW3, 2     ); /* PIC1はIRQ2にて接続 */
	_io_out8(PIC1_ICW4, 0x01  ); /* ノンバッファモード */

	_io_out8(PIC0_IMR,  0xfb  ); /* 11111011 PIC1以外は全て禁止 */
	_io_out8(PIC1_IMR,  0xff  ); /* 11111111 全ての割り込みを受け付けない */

}


#define PORT_KEYDAT		0x0060

struct FIFO8 keyfifo;


void inthandler21(int *esp)
/* PS/2キーボードからの割り込み */
{
	unsigned char data;
	
 	_io_out8(PIC0_OCW2, 0x61);	/* IRQ-01受付完了をPICに通知 */
 	data = _io_in8(PORT_KEYDAT);

	fifo8_put(&keyfifo, data);

	return;
}

void inthandler2c(int *esp)
/* PS/2マウスからの割り込み */
{
	struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;
	boxfill8((char *)binfo->vram, binfo->scrnx, COL8_000000, 0, 0, 32 * 8 - 1, 15);
	putfonts8_asc((char *)binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, "INT 2C (IRQ-12) : PS/2 mouse");
	for (;;) {
		_io_hlt();
	}
}

void inthandler27(int *esp)
/* PIC0からの不完全割り込み対策 */
/* Athlon64X2機などではチップセットの都合によりPICの初期化時にこの割り込みが1度だけおこる */
/* この割り込み処理関数は、その割り込みに対して何もしないでやり過ごす */
/* なぜ何もしなくていいの？
	→  この割り込みはPIC初期化時の電気的なノイズによって発生したものなので、
		まじめに何か処理してやる必要がない。									*/
{
	struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;  
	putfonts8_asc((char *)binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, "INT 27 (IRQ-7) : xxx");  
	_io_out8(PIC0_OCW2, 0x67); /* IRQ-07受付完了をPICに通知(7-1参照) */
	return;
}
