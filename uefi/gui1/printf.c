
#include "stdarg.h"
#include "common.h"

// TODO: automaton, global に依存しているのは仕方ないとして現在状態, 入力, 遷移先, 副作用については pair で扱うようにする
// TODO: putc 等を macro か何かにしておく. (将来このコードを kernel にもっていく予定なので)
// TODO: width の二文字以上についての取扱 (ll とか)
// TODO: 未実装 parameter, precision


typedef enum _MSG_TYPE {
    PRINTABLE,
    VARIABLE_KEY,
    ESCAPE_SEQ_KEY,
} MSG_TYPE;

typedef enum _STATE {
    IDLE,
    READ_VARIABLE,
    READ_VARIABLE_FLAGS,
    READ_VARIABLE_WIDTH,
    READ_VARIABLE_PRECISION,
    READ_VARIABLE_LENGTH,
    READ_VARIABLE_TYPE,
    READ_ESCAPE_SEQUENCE,
    FIN,
    ERR,
} STATE;


#define VARIABLE_FLAGS_APOSTROPHE (0x01 << 1)
#define VARIABLE_FLAGS_MINUS      (0x01 << 2)
#define VARIABLE_FLAGS_PLUS       (0x01 << 3)
#define VARIABLE_FLAGS_SPACE      (0x01 << 4)
#define VARIABLE_FLAGS_ZERO       (0x01 << 5)
#define VARIABLE_FLAGS_HASH       (0x01 << 6)

typedef enum _VARIABLE_LENGTH {
    VARIABLE_LENGTH_NULL = 0,    
    VARIABLE_LENGTH_hh,
    VARIABLE_LENGTH_h,
    VARIABLE_LENGTH_ll,
    VARIABLE_LENGTH_l,
    VARIABLE_LENGTH_L,
    VARIABLE_LENGTH_z,
    VARIABLE_LENGTH_j,
    VARIABLE_LENGTH_t,
    VARIABLE_LENGTH_MAX,    
} VARIABLE_LENGTH;

// 
typedef enum _VARIABLE_TYPE {
    VARIABLE_TYPE_NULL = 0,
    VARIABLE_TYPE_SIGNED_INT,                   // d, i
    VARIABLE_TYPE_UNSIGNED_INT,                 // u
    VARIABLE_TYPE_FIXED_POINT,                  // f
    VARIABLE_TYPE_FIXED_POINT_UPPER_CASE,       // F
    VARIABLE_TYPE_DOUBLE_EXP,                   // e
    VARIABLE_TYPE_DOUBLE_EXP_UPPER_CASE,        // E
    VARIABLE_TYPE_DOUBLE_EXP_NORMAL,            // g
    VARIABLE_TYPE_DOUBLE_EXP_NORMAL_UPPER_CASE, // G
    VARIABLE_TYPE_UNSIGNED_INT_HEX,             // x
    VARIABLE_TYPE_UNSIGNED_INT_HEX_UPPER_CASE,  // X
    VARIABLE_TYPE_UNSIGNED_INT_OCTAL,           // o
    VARIABLE_TYPE_STRING,                       // s
    VARIABLE_TYPE_CHAR,                         // c
    VARIABLE_TYPE_POINTER,                      // p
    VARIABLE_TYPE_DOUBLE_HEX,                   // a
    VARIABLE_TYPE_DOUBLE_HEX_UPPER_CASE,        // A
    VARIABLE_TYPE_NOTHING,                      // n
    VARIABLE_TYPE_MAX,
} VARIABLE_TYPE;


// %[parameter][flags][width][.precision][length]type
typedef struct _VARIABLE {
    int parameter; // not implement
    int flags;
    int width;
    int precision; // not implement
    VARIABLE_LENGTH length;
    VARIABLE_TYPE type;
} VARIABLE;


// https://ja.wikipedia.org/wiki/Printf
static char flags[] = {'-', '+', ' ', '#', '0'};
static char length_key[] = {'h', 'l', 'L', 'z', 'j', 't'};
static char type[] = {'d', 'i', 'u', 'f', 'F', 'e', 'E', 'g', 'G', 'x', 'X', 'o', 's', 'c', 'p', 'a', 'A', 'n'};

static STATE state = IDLE;

static VARIABLE variable;

static void parse_init();
static void parse(char c);
static void set_flags(char c);
static void set_width(char c);
static void set_precision(char c);
static void set_length(char c);
static void set_type(char c);
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
    state = IDLE;
}


static void parse(char c) {

    MSG_TYPE msg;
    
    switch (state) {
    case IDLE:
	if (is_escape_key(c)) {
	    state = READ_ESCAPE_SEQUENCE;
	}
	else if (is_variable_key(c)) {
	    memset(variable, 0x00, sizeof(variable));	    
	    state = READ_VARIABLE;
	}
	else if (is_printable_char(c)) {
	    state = IDLE;
	    putc(c);
	}    
	break;
    case READ_VARIABLE:
	if (is_variable_flags(c)) {
	    set_flags(c);
	    state = READ_VARIABLE_FLAGS;	    
	}
	else if (is_numeric(c)) { // width
	    set_width(c);
	    state = READ_VARIABLE_WIDTH;
	}
	else if (is_period(c)) {  // precision
	    set_precision(c);
	    state = READ_VARIABLE_PRECISION;
	}
	else if (is_variable_length(c)) {
	    set_length(c);
	    state = READ_VARIABLE_LENGTH;	    
	}
	else if (is_variable_type(c)) {
	    set_type(c);
	    state = READ_VARIABLE_TYPE;
	}	
	else {
	    // only % case?
	    putc(L'%');
	    state = READ_VARIABLE_TYPE;	    
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


static void set_width(char c) {

    int prv = variable.width;
    int cur = c - '0';
    int new = prv*10+cur;
    
    variable.width = new;
}


static void set_precision(char c) {
    
    int prv = variable.precision;
    int cur = c - '0';
    int new = prv*10+cur;
    
    variable.precision = new;
}


static void set_length(char c) {
    
    int prv = variable.length;

    if (VARIABLE_LENGTH_NULL == prv) {
	switch (c) {
	case 'h':
	    variable.length = VARIABLE_LENGTH_h;
	    break;
	case 'l':
	    variable.length = VARIABLE_LENGTH_l;	    
	    break;
	case 'L':
	    variable.length = VARIABLE_LENGTH_L;
	    break;
	case 'z':
	    variable.length = VARIABLE_LENGTH_z;
	    break;
	case 'j':
	    variable.length = VARIABLE_LENGTH_j;
	    break;
	case 't':
	    variable.length = VARIABLE_LENGTH_t;
	    break;
	default:
		// TODO: error
	    break;
	}
    }
    else {
	switch (prv) {
	case VARIABLE_LENGTH_h:
	    if ('h' == c) {
		variable.length = VARIABLE_LENGTH_hh;
	    }
	    else {
		    // TODO: error
	    }
	    break;
	case VARIABLE_LENGTH_l:
	    if ('l' == c) {
		variable.length = VARIABLE_LENGTH_ll;
	    }
	    else {
		    // TODO: error
	    }	    
	    break;
	default:
		// TODO: error
	    break;
	}
    }
}


static void set_type(char c) {
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
