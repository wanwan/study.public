
#include "shell.h"

#define MAX_COMMAND_LEN (128)

void shell() {

    int loop = 1;
    unsigned short com[MAX_COMMAND_LEN];
    
    while(loop) {
	puts(L"poiOS> ");
	if (gets(com, MAX_COMMAND_LEN) <= 0) {
	    continue;
	}

	if (!strcmp(com, L"hello")) {
	    puts(L"Hello UEFI \r\n");
	}
	else {
	    puts(L"Unknown command \r\n");
	}
	
    }
    
}
