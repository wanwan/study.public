
#include "stdarg.h"

// https://ja.wikipedia.org/wiki/Printf
static char flags[] = {'-', '+', ' ', '#', '0'};
static char width[][] = {"hh", "h", "ll", "l", "j", "z", "t", "l"};


void printf(const char *format, ...) {

    va_list args;
    int i = 0;

    va_start(args, format);

    while ('\0' != format[i]) {


	i++;
    }
    
    va_end(args);
}


int is_printable_char(char c) {

    if (c) {
       
    }
}
