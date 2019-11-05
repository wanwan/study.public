int _api_openwin(char *buf, int xsiz, int ysiz, int col_inv, char *title);
void _api_initmalloc(void);
char *_api_malloc(int size);
void _api_refreshwin(int win, int x0, int y0, int x1, int y1);
void _api_linewin(int win, int x0, int y0, int x1, int y1, int col);
int _api_getkey(int mode);
void _api_end(void);

void HariMain(void)
{
	char *buf;
	int win, x, y, r, g, b;
	_api_initmalloc();
	buf = _api_malloc(144 * 164);
	win = _api_openwin(buf, 144, 164, -1, "color");
	for (y = 0; y < 128; y++) {
		for (x = 0; x < 128; x++) {
			r = x * 2;
			g = y * 2;
			b = 0;
			buf[(x + 8) + (y + 28) * 144] = 16 + (r / 43) + (g / 43) * 6 + (b / 43) * 36;
		}
	}
	_api_refreshwin(win, 8, 28, 136, 156);
	_api_getkey(1); /* てきとうなキー入力を待つ */
	_api_end();
}
