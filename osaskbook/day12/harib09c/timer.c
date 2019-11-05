/* タイマ関係 */

#include "bootpack.h"

#define PIT_CTRL	0x0043
#define PIT_CNT0	0x0040

struct TIMERCTL timerctl;

void init_pit(void)
{
	_io_out8(PIT_CTRL, 0x34);
	_io_out8(PIT_CNT0, 0x9c);
	_io_out8(PIT_CNT0, 0x2e);
	timerctl.count = 0;
	timerctl.timeout = 0;
	return;
}


void inthandler20(int *esp)
{
	_io_out8(PIC0_OCW2, 0x60);	/* IRQ-00受付完了をPICに通知 */
	timerctl.count++;	
	if (timerctl.timeout > 0) { /* タイムアウトが設定されている */
		timerctl.timeout--;
		if (timerctl.timeout == 0) {
			fifo8_put(timerctl.fifo, timerctl.data);
		}
	}
	
	return;
}


void settimer(unsigned int timeout, struct FIFO8 *fifo, unsigned char data)
{
	int eflags;
	eflags = _io_load_eflags();
	_io_cli();
	timerctl.timeout = timeout;
	timerctl.fifo = fifo;
	timerctl.data = data;
	_io_store_eflags(eflags);
	return;
}
