#include <stdio.h>
#include "apilib.h"

void HariMain(void)
{    
        char *buf, s[12];// = "00000:03:00";
	int win, timer, sec = 0, min = 0, hou = 0;
	int key;	
	api_initmalloc();
	buf = api_malloc(150 * 50);
	win = api_openwin(buf, 150, 50, -1, "noodle");
	timer = api_alloctimer();
	api_inittimer(timer, 128);	
//	sprintf(s, "%4d:%02d:%02d", hou, min, sec);
//	_api_boxfilwin(win, 5, 27, 140, 41, 7 /* 白 */);
//	_api_putstrwin(win, 5, 27, 0 /* 黒 */, 11, s);		
//	_api_settimer(timer, 100);	/* 1秒間 */
	

	for (;;) {
//		sprintf(s, "%4d:%02d:%02d", hou, min, sec);
	        sprintf(s, "%3d:%02d:%02d", hou, min, sec);
		api_boxfilwin(win, 5, 27, 140, 41, 7 /* 白 */);
		api_putstrwin(win, 5, 27, 0 /* 黒 */, 11, s);
		api_settimer(timer, 100);	/* 1秒間 */
		if (api_getkey(1) != 128) {
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
	    key = api_getkey(1);
	    if (key == 0x0a) {
		break; /* Enterならbreak; */
	    }
	    else if (key == 128) {
		api_debug('t');
	    }
	}
#endif	
	
	api_end();
}
