
#include "stdarg.h"
#include "common.h"

typedef enum _MSG_TYPE {
    PRINTABLE,
    VARIABLE_KEY,
    ESCAPE_SEQ_KEY,
} MSG_TYPE;

typedef enum _STATUS {
    IDLE,
    READ_VARIABLE,
    READ_VARIABLE_FLAGS,
    READ_VARIABLE_WIDTH,
    READ_VARIABLE_PRECISION,
    READ_VARIABLE_LENGTH,
    READ_VARIABLE_TYPE,
    READ_ESCAPE_SEQUENCE,
} STATUS;


#define VARIABLE_FLAGS_APOSTROPHE (0x01 << 1)
#define VARIABLE_FLAGS_MINUS      (0x01 << 2)
#define VARIABLE_FLAGS_PLUS       (0x01 << 3)
#define VARIABLE_FLAGS_SPACE      (0x01 << 4)
#define VARIABLE_FLAGS_ZERO       (0x01 << 5)
#define VARIABLE_FLAGS_HASH       (0x01 << 6)

// 
typedef enum _VARIABLE_TYPE {
    SIGNED_INT,                   // d, i
    UNSIGNED_INT,                 // u
    FIXED_POINT,                  // f
    FIXED_POINT_UPPER_CASE,       // F
    DOUBLE_EXP,                   // e
    DOUBLE_EXP_UPPER_CASE,        // E
    DOUBLE_EXP_NORMAL,            // g
    DOUBLE_EXP_NORMAL_UPPER_CASE, // G
    UNSIGNED_INT_HEX,             // x
    UNSIGNED_INT_HEX_UPPER_CASE,  // X
    UNSIGNED_INT_OCTAL,           // o
    STRING,                       // s
    CHAR,                         // c
    POINTER,                      // p
    DOUBLE_HEX,                   // a
    DOUBLE_HEX_UPPER_CASE,        // A
    NOTHING,                      // n
} VARIABLE_TYPE;


// %[parameter][flags][width][.precision][length]type
typedef struct _VARIABLE {
    int parameter; // not implement
    int flags;
    int width;
    int precision;
    int length;
    VARIABLE_TYPE type;
} VARIABLE;


// https://ja.wikipedia.org/wiki/Printf
static char flags[] = {'-', '+', ' ', '#', '0'};

static char length_key[] = {'h', 'l', 'L', 'z', 'j', 't'};
static char *length[] = {"hh", "h", "ll", "l", "L", "z", "j", "t"};
static char type[] = {'d', 'i', 'u', 'f', 'F', 'e', 'E', 'g', 'G', 'x', 'X', 'o', 's', 'c', 'p', 'a', 'A', 'n'};

static STATUS status = IDLE;

static VARIABLE variable;

static void parse_init();
static void parse(char c);
static void set_flags(char c);
static int is_escape_key(char c);
static int is_printable_char(char c);
static int is_variable_key(char c);
static int is_variable_flags(char c);
static int is_numeric (char c);
static int is_period (char c);
static int is_variable_length(char c);
static int is_variable_type(char c);


void printf(const char *format, ...) {

    va_list args;
    int i = 0;

    char cur;
    
    va_start(args, format);

    while ('\0' != format[i]) {
	cur = format[i];
	parse(cur);
	i++;
    }
    
    va_end(args);
}



static void parse_init() {
    status = IDLE;
}


static void parse(char c) {

    MSG_TYPE msg;
    
    switch (status) {
    case IDLE:
	if (is_escape_key(c)) {
	    status = READ_ESCAPE_SEQUENCE;
	}
	else if (is_variable_key(c)) {
	    status = READ_VARIABLE;
	}
	else if (is_printable_char(c)) {
	    status = IDLE;
	    putc(c);
	}    
	break;
    case READ_VARIABLE:
	if (is_variable_flags(c)) {
	    set_flags(c);
	    status = READ_VARIABLE_FLAGS;	    
	}
	else if (is_numeric(c)) { // width
	    status = READ_VARIABLE_WIDTH;
	}
	else if (is_period(c)) {  // precision
	    status = READ_VARIABLE_PRECISION;
	}
	else if (is_variable_length(c)) {
	    status = READ_VARIABLE_LENGTH;	    
	}
	else if (is_variable_type(c)) {
	    status = READ_VARIABLE_TYPE;
	}	
	else {
	    // only % case?
	    putc(L'%');
	}    
	break;

    case READ_VARIABLE_FLAGS:
	break;
    case READ_VARIABLE_WIDTH:
	break;
    case READ_VARIABLE_PRECISION:
	break;
    case READ_VARIABLE_LENGTH:
	break;
    case READ_VARIABLE_TYPE:
	break;
	
    case READ_ESCAPE_SEQUENCE:
	
	break;
    }
}


static void set_flags(char c) {

    switch (c) {
    case '\'':
	variable.flags |= VARIABLE_FLAGS_APOSTROPHE;
	break;
    case '-':
	variable.flags |= VARIABLE_FLAGS_MINUS;
	break;
    case '+':
	variable.flags |= VARIABLE_FLAGS_PLUS;
	break;
    case ' ':
	variable.flags |= VARIABLE_FLAGS_SPACE;
	break;
    case '0':
	variable.flags |= VARIABLE_FLAGS_ZERO;
	break;
    case '#':
	variable.flags |= VARIABLE_FLAGS_HASH;
	break;
    }
    
}


static int is_escape_key(char c) {
    
    if ('\\' == c ) {
	return 1;
    }
    return 0;
}


static int is_printable_char(char c) {

    if (('\\' != c) && ('!' <= c && c <= '~')) {
	return 1;
    }

    return 0;
}


static int is_variable_key(char c) {
    if ('%' == c) {
	return 1;
    }
    return 0;
    
}

static int is_variable_flags(char c) {

    int length = sizeof(flags) / sizeof(char);
    int i = 0;
    
    for (i = 0; i < length; i++) {
	if (c == flags[i]) {
	    return 1;
	}
    }
    return 0;
    
}


static int is_numeric (char c) {
    if ('0' <= c && c <= '9' ) {
	return 1;
    }
    return 0;
}


static int is_period (char c) {
    if ('.' == c) {
	return 1;
    }
    return 0;
}


static int is_variable_length(char c) {

    int length = sizeof(length_key) / sizeof(char);
    int i = 0;
    
    for (i = 0; i < length; i++) {
	if (c == length_key[i]) {
	    return 1;
	}
    }
    return 0;
    
}


static int is_variable_type(char c) {

    int length = sizeof(type) / sizeof(char);
    int i = 0;
    
    for (i = 0; i < length; i++) {
	if (c == type[i]) {
	    return 1;
	}
    }
    return 0;

}
