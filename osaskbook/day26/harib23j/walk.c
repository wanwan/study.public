int _api_openwin(char *buf, int xsiz, int ysiz, int col_inv, char *title);
void _api_putstrwin(int win, int x, int y, int col, int len, char *str);
void _api_boxfilwin(int win, int x0, int y0, int x1, int y1, int col);
void _api_initmalloc(void);
char *_api_malloc(int size);
void _api_refreshwin(int win, int x0, int y0, int x1, int y1);
void _api_linewin(int win, int x0, int y0, int x1, int y1, int col);
void _api_closewin(int win);
int _api_getkey(int mode);
void _api_end(void);

void HariMain(void)
{
	char *buf;
	int win, i, x, y;
	_api_initmalloc();
	buf = _api_malloc(160 * 100);
	win = _api_openwin(buf, 160, 100, -1, "walk");
	_api_boxfilwin(win, 4, 24, 155, 95, 0 /* 黒 */);
	x = 76;
	y = 56;
	_api_putstrwin(win, x, y, 3 /* 黄 */, 1, "*");
	for (;;) {
		i = _api_getkey(1);
		_api_putstrwin(win, x, y, 0 /* 黒 */, 1, "*"); /* 黒で消す */
		if (i == '4' && x >   4) { x -= 8; }
		if (i == '6' && x < 148) { x += 8; }
		if (i == '8' && y >  24) { y -= 8; }
		if (i == '2' && y <  80) { y += 8; }
		if (i == 0x0a) { break; } /* Enterで終了 */
		_api_putstrwin(win, x, y, 3 /* 黄 */, 1, "*");
	}	
	_api_closewin(win);
	_api_end();
}
