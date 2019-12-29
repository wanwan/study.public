int _api_openwin(char *buf, int xsiz, int ysiz, int col_inv, char *title);
void _api_initmalloc(void);
char *_api_malloc(int size);
void _api_refreshwin(int win, int x0, int y0, int x1, int y1);
void _api_linewin(int win, int x0, int y0, int x1, int y1, int col);
int _api_getkey(int mode);
void _api_end(void);

unsigned char rgb2pal(int r, int g, int b, int x, int y);

void HariMain(void)
{
	char *buf;
	int win, x, y;
	_api_initmalloc();
	buf = _api_malloc(144 * 164);
	win = _api_openwin(buf, 144, 164, -1, "color2");
	for (y = 0; y < 128; y++) {
		for (x = 0; x < 128; x++) {
			buf[(x + 8) + (y + 28) * 144] = rgb2pal(x * 2, y * 2, 0, x, y);
		}
	}
	_api_refreshwin(win, 8, 28, 136, 156);
	_api_getkey(1); /* �Ă��Ƃ��ȃL�[���͂�҂� */
	_api_end();
}

unsigned char rgb2pal(int r, int g, int b, int x, int y)
{
	static int table[4] = { 3, 1, 0, 2 };
	int i;
	x &= 1; /* ��������� */
	y &= 1;
	i = table[x + y * 2];	/* ���ԐF����邽�߂̒萔 */
	r = (r * 21) / 256;	/* ����� 0�`20 �ɂȂ� */
	g = (g * 21) / 256;
	b = (b * 21) / 256;
	r = (r + i) / 4;	/* ����� 0�`5 �ɂȂ� */
	g = (g + i) / 4;
	b = (b + i) / 4;
	return 16 + r + g * 6 + b * 36;
}
