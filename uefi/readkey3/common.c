
#include "efi.h"
#include "common.h"

extern EFI_SYSTEM_TABLE    *system_table;

void putc(unsigned short c) {

    unsigned short str[3] = L" ";
    str[0] = c;

#if 0    
    //str[1] = 0x00;
    if ('\r' != c) {
	str[0] = c;
    }
    else {
	str[0] = '\r';
	str[1] = '\n';
	str[2] = '\0';	    
    }
#endif
    
    system_table->ConOut->OutputString(system_table->ConOut, str);
}


void puts(unsigned short *s) {
    
    system_table->ConOut->OutputString(system_table->ConOut, s);
}


unsigned short getc(void) {

    EFI_INPUT_KEY key;
    unsigned long long waitidx;

    system_table->BootServices->WaitForEvent(1, &(system_table->ConIn->WaitForKey), &waitidx);

    // なぜ while? getc の仕様的に最初の一文字を戻すだと思うのだが. wait event の戻りと取れるまでラグがある?
    while (system_table->ConIn->ReadKeyStroke(system_table->ConIn, &key));

    return key.UnicodeChar;
}


unsigned int gets(unsigned short *buf, unsigned int buf_size) {

    unsigned int i;

    for (i = 0; i < buf_size - 1; ) {
	buf[i] = getc();
	puts(buf[i]);
	if (buf[i] == L'\r') {
	    putc(L'\r');
	    putc(L'\n');
	    break;
	}
	i++;
    }
    buf[i] = L'\0';

    return i;
}



int strcmp(const unsigned short *s1, const unsigned short *s2) {

    char is_equal = 1;

    for (; (*s1 != L'\0') && (*s2 != L'\0'); s1++, s2++) {
	if (*s1 != *s2) {
	    is_equal = 0;
	    break;
	}
    }

    if (is_equal) {
	if (*s1 != L'\0') {
	    return 1;
	}
	else if (*s2 != L'\0') {
	    return -1;
	}
	else {
	    return 0;
	}
    }
    else {
	return (int)(*s1 - *s2);
    }
    
}    
