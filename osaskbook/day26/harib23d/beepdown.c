void _api_end(void);
int _api_getkey(int mode);
int _api_alloctimer(void);
void _api_inittimer(int timer, int data);
void _api_settimer(int timer, int time);
void _api_beep(int tone);

void HariMain(void)
{
	int i, timer;
	timer = _api_alloctimer();
	_api_inittimer(timer, 128);
	for (i = 20000000; i >= 20000; i -= i / 100) {
		/* 20KHz〜20Hz : 人間に聞こえる音の範囲 */
		/* iは1%ずつ減らされていく */
		_api_beep(i);
		_api_settimer(timer, 1);		/* 0.01秒 */
		if (_api_getkey(1) != 128) {
			break;
		}
	}
	_api_beep(0);
	_api_end();
}
