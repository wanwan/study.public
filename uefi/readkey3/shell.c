
#include "shell.h"

#define MAX_COMMAND_LEN (128)

int is_enter(unsigned short key) {

    if (L'\r' == key) {
	return 1;
    }

    return 0;
}


void shell() {

    int loop = 1;
    unsigned short com[MAX_COMMAND_LEN];
    unsigned short key;
    int idx = 0;
    
    while(loop) {
	idx = 0;
	puts(L"poiOS> ");
	while ((key = getc())) {
	    if (idx <= (MAX_COMMAND_LEN - 1)) {
		
		com[idx] = key;
		
		if (is_enter(key)) {
		    com[idx] = '\0';
		    putc(L'\r');
		    putc(L'\n');		    
		    break;
		}
		else {
		    putc(key);
		}
		idx++;
	    }
	    else {
		puts(L"one line is so long \r\n");		
		continue;		
	    }
	}

#if 0	
	if (gets(com, MAX_COMMAND_LEN) <= 0) {
	    continue;
	}
#endif
	
	if (!strcmp(com, L"hello")) {
	    puts(L"Hello UEFI \r\n");
	}
	else {
	    puts(L"Unknown command \r\n");
	}
	
    }
    
}
