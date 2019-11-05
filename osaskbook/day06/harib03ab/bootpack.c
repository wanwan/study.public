#include <stdio.h>

void _io_hlt(void);
void _io_cli(void);
void _io_out8(int port, int data);
int _io_load_eflags(void);
void _io_store_eflags(int eflags);
void _load_gdtr(int limit, int addr);
void _load_idtr(int limit, int addr);

void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);
void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);
void init_screen(char *vram, int x, int y);
void putfont8(char *vram, int xsize, int x, int y, char c, char *font);
void putfonts8_asc(char *vram, int xsize, int x, int y, char c, unsigned char *s);
void init_mouse_cursor8(char *mouse, char bc);
void putblock8_8(char *vram, int vxsize, int pxsize,
	int pysize, int px0, int py0, char *buf, int bxsize);


#define COL8_000000		0
#define COL8_FF0000		1
#define COL8_00FF00		2
#define COL8_FFFF00		3
#define COL8_0000FF		4
#define COL8_FF00FF		5
#define COL8_00FFFF		6
#define COL8_FFFFFF		7
#define COL8_C6C6C6		8
#define COL8_840000		9
#define COL8_008400		10
#define COL8_848400		11
#define COL8_000084		12
#define COL8_840084		13
#define COL8_008484		14
#define COL8_848484		15

struct BOOTINFO {
	volatile char cyls, leds, vmode, reserve;
	volatile short scrnx, scrny;
	volatile char *vram;
};

struct SEGMENT_DESCRIPTOR {
	volatile short limit_low, base_low;
	volatile char base_mid, access_right;
	volatile char limit_high, base_high;
};

struct GATE_DESCRIPTOR {
	volatile short offset_low, selector;
	volatile char dw_count, access_right;
	volatile short offset_high;
};


void init_gdtidt(void);
void set_segmdesc(struct SEGMENT_DESCRIPTOR *sd, unsigned int limit, int base, int ar);
void set_gatedesc(struct GATE_DESCRIPTOR *gd, int offset, int selector, int ar);



void HariMain(void)
{
	struct BOOTINFO *binfo;
	char s[40], mcursor[256];
	int mx, my;
	
	binfo = (struct BOOTINFO *) 0x0ff0;

	init_gdtidt();	
	init_palette();
	init_screen((char *)binfo->vram, binfo->scrnx, binfo->scrny);

	mx = (binfo->scrnx - 16) / 2; /* 画面中央になるように座標計算 */
	my = (binfo->scrny - 28 - 16) / 2;
	init_mouse_cursor8(mcursor, COL8_008484);
	putblock8_8((char *)binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);
	sprintf(s, "(%d, %d)", mx, my);
	putfonts8_asc((char *)binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);
	
	for (;;) {
		_io_hlt();
	}
}


