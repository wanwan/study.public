int _api_openwin(char *buf, int xsiz, int ysiz, int col_inv, char *title);
void _api_putstrwin(int win, int x, int y, int col, int len, char *str);
void _api_boxfilwin(int win, int x0, int y0, int x1, int y1, int col);
void _api_end(void);

char buf[150 * 50];

void HariMain(void)
{
	int win;
	win = _api_openwin(buf, 150, 50, -1, "hello");
	_api_boxfilwin(win,  8, 36, 141, 43, 3 /* â© */);
	_api_putstrwin(win, 28, 28, 0 /* çï */, 12, "hello, world");
	_api_end();
}
