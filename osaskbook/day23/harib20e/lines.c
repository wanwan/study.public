int _api_openwin(char *buf, int xsiz, int ysiz, int col_inv, char *title);
void _api_initmalloc(void);
char *_api_malloc(int size);
void _api_refreshwin(int win, int x0, int y0, int x1, int y1);
void _api_linewin(int win, int x0, int y0, int x1, int y1, int col);
void _api_closewin(int win);
void _api_end(void);

void HariMain(void)
{
	char *buf;
	int win, i;
	_api_initmalloc();
	buf = _api_malloc(160 * 100);
	win = _api_openwin(buf, 160, 100, -1, "lines");
	for (i = 0; i < 8; i++) {
		_api_linewin(win + 1,  8, 26, 77, i * 9 + 26, i);
		_api_linewin(win + 1, 88, 26, i * 9 + 88, 89, i);
	}
	_api_refreshwin(win,  6, 26, 154, 90);
	_api_closewin(win);
	_api_end();
}
