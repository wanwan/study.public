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
