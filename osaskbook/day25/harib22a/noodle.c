#include <stdio.h>

int _api_openwin(char *buf, int xsiz, int ysiz, int col_inv, char *title);
void _api_putstrwin(int win, int x, int y, int col, int len, char *str);
void _api_boxfilwin(int win, int x0, int y0, int x1, int y1, int col);
void _api_initmalloc(void);
char *_api_malloc(int size);
int _api_getkey(int mode);
int _api_alloctimer(void);
void _api_inittimer(int timer, int data);
void _api_settimer(int timer, int time);
void _api_end(void);
void _api_debug(unsigned char x);


void HariMain(void)
{    
        char *buf, s[12];// = "00000:03:00";
	int win, timer, sec = 0, min = 0, hou = 0;
	int key;	
	_api_initmalloc();
	buf = _api_malloc(150 * 50);
	win = _api_openwin(buf, 150, 50, -1, "noodle");
	timer = _api_alloctimer();
	_api_inittimer(timer, 128);	
//	sprintf(s, "%4d:%02d:%02d", hou, min, sec);
//	_api_boxfilwin(win, 5, 27, 140, 41, 7 /* 白 */);
//	_api_putstrwin(win, 5, 27, 0 /* 黒 */, 11, s);		
//	_api_settimer(timer, 100);	/* 1秒間 */
	

	for (;;) {
//		sprintf(s, "%4d:%02d:%02d", hou, min, sec);
	        sprintf(s, "%3d:%02d:%02d", hou, min, sec);
		_api_boxfilwin(win, 5, 27, 140, 41, 7 /* 白 */);
		_api_putstrwin(win, 5, 27, 0 /* 黒 */, 11, s);
		_api_settimer(timer, 100);	/* 1秒間 */
		if (_api_getkey(1) != 128) {
			break;
		}

//		_api_debug('t');
		
		sec++;
		if (sec == 60) {
			sec = 0;
			min++;
			if (min == 60) {
				min = 0;
				hou++;
			}
		}
	}

#if 0	
	for (;;) {
	    key = _api_getkey(1);
	    if (key == 0x0a) {
		break; /* Enterならbreak; */
	    }
	    else if (key == 128) {
		_api_debug('t');
	    }
	}
#endif	
	
	_api_end();
}
