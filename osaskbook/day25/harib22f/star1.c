int _api_openwin(char *buf, int xsiz, int ysiz, int col_inv, char *title);
void _api_boxfilwin(int win, int x0, int y0, int x1, int y1, int col);
void _api_initmalloc(void);
char *_api_malloc(int size);
void _api_point(int win, int x, int y, int col);
void _api_end(void);

void HariMain(void)
{
	char *buf;
	int win;
	_api_initmalloc();
	buf = _api_malloc(150 * 100);
	win = _api_openwin(buf, 150, 100, -1, "star1");
	_api_boxfilwin(win,  6, 26, 143, 93, 0 /* 黒 */);
	_api_point(win, 75, 59, 3 /* 黄 */);
	_api_end();
}
