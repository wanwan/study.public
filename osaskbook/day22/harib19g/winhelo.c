int _api_openwin(char *buf, int xsiz, int ysiz, int col_inv, char *title);
void _api_end(void);

char buf[150 * 50];

void HariMain(void)
{
	int win;
	win = _api_openwin(buf, 150, 50, -1, "hello");
	_api_end();
}
