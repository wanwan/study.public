#include <stdarg.h>

#define TRUE (1)
#define FALSE (0)

//10進数からASCIIコードに変換
static int dec2asc (char *str, int dec, int zerocnt, int padding) {
    int len = 0, len_buf; //桁数
    int buf[10];
    int i;
    int negative = FALSE;

    if (dec < 0) {
      dec *= -1;
      negative = TRUE;
    }
    
    while (1) { //10で割れた回数（つまり桁数）をlenに、各桁をbufに格納
        buf[len++] = dec % 10;
        if (dec < 10) break;
        dec /= 10;
    }
    len_buf = (negative == FALSE) ? len : len + 1;

    while (zerocnt > 0 && zerocnt > len) {
      zerocnt--;
      buf[len++] = 0;
      len_buf = len;
    }

    if (negative) {
      if (padding > 0 && padding > (len+1)) {
	for (i = 0; i < (padding-(len+1)); i++) {
	  *(str++) = ' ';	
	}
	len_buf = padding;
      }
    }
    else {
      if (padding > 0 && padding > len) {
	for (i = 0; i < (padding-len); i++) {
	  *(str++) = ' ';	
	}
	len_buf = padding;
      }
    }

    if (negative) {
        *(str++) = '-';
    }
    while (len) {
        *(str++) = buf[--len] + 0x30;
    }
    return len_buf;
}

//16進数からASCIIコードに変換
static int hex2asc (char *str, int dec, int zerocnt, int padding) {
  //16で割れた回数（つまり桁数）をlenに、各桁をbufに格納
    int len = 0, len_buf; //桁数
    int buf[10];
    int i;
    
    while (1) {
        buf[len++] = dec % 16;
        if (dec < 16) break;
        dec /= 16;
    }
    len_buf = len;


    while (zerocnt > 0 && zerocnt > len) {
      zerocnt--;
      buf[len++] = 0;
      len_buf = len;
    }

    while (len) {
        len --;
        *(str++) = (buf[len]<10)?(buf[len] + 0x30):(buf[len] - 9 + 0x60);
    }
    
    return len_buf;
}


static int hex2ASC (char *str, int dec, int zerocnt, int padding) {
  //16で割れた回数（つまり桁数）をlenに、各桁をbufに格納
    int len = 0, len_buf; //桁数
    int buf[10];
    int i;
    
    while (1) {
        buf[len++] = dec % 16;
        if (dec < 16) break;
        dec /= 16;
    }
    len_buf = len;


    while (zerocnt > 0 && zerocnt > len) {
      zerocnt--;
      buf[len++] = 0;
      len_buf = len;
    }

    while (len) {
        len --;
        *(str++) = (buf[len]<10)?(buf[len] + 0x30):(buf[len] - 9 + 0x40);
    }
    
    return len_buf;
}






void sprintf (char *str, char *fmt, ...) {
    va_list list;
    int i, len;
    int zerocnt = 0;
    int padding = 0;    
    va_start (list, fmt);

    while (*fmt) {
        if(*fmt=='%') {
	retry:	  
            fmt++;
            switch(*fmt){
	    case '0':
	      fmt++;	      
	      zerocnt = (*fmt) - 0x30;
	      goto retry;
	    case '1':
	    case '2':
	    case '3':
	    case '4':
	    case '5':
	    case '6':
	    case '7':
	    case '8':
	    case '9':	      
	      padding = (*fmt) - 0x30;
	      goto retry;
	    case 'd':
	    case 'D':
	      len = dec2asc(str, va_arg (list, int), zerocnt, padding);
	      break;
	    case 'x':
	      len = hex2asc(str, va_arg (list, int), zerocnt, padding);
	      break;
	    case 'X':
	      len = hex2ASC(str, va_arg (list, int), zerocnt, padding);
	      break;	      
            }
            str += len; fmt++;
        } else {
            *(str++) = *(fmt++);
        }	
    }
    *str = 0x00; //最後にNULLを追加
    va_end (list);
}
