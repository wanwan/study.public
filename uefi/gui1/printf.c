
#include "stdarg.h"

// https://ja.wikipedia.org/wiki/Printf
static char flags[] = {'-', '+', ' ', '#', '0'};
static char *width[] = {"hh", "h", "ll", "l", "j", "z", "t", "l"};
static char variable_char = '%';
static char escape_char = '%';

typedef enum _STATE {
    IDLE,
    READ_VARIABLE,
    READ_ESCAPE,    
} STATE;


void printf(const char *format, ...) {

    va_list args;
    int i = 0;

    STATE state = IDLE;
    char cur;
    
    va_start(args, format);

    while ('\0' !=) {
	cur = format[i];
	
	switch (state) {
	case IDLE:
	    if (if_variable_char(cur)) {
	    }
	    else if (is_variable_char(cur)) {
	    }
	    else if (is_printable_char(cur)) {
	    }
	    else {
	    }	    	    
	    break;
	case READ_VARIABLE:
	    break;
	case READ_ESCAPE:
	    break;	    
	}

	i++;
    }
    
    va_end(args);
}


void parser (char input) {

}



int is_printable_char(char c) {

    if (c) {
       
    }

    return 0;
}


int is_variable_char(char c) {

    if ('%' == c) {
	return 1;
    }
    return 0;
}
