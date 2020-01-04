
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXBUF (256)
#define FILENAME "a.bdf"
#define OUTPUT_FILENAME "o.c"


char header[] = "#define FONTDATAMAX 4096 \n\nconst unsigned char fontdata_8x16[FONTDATAMAX] = {\n\n";
char footer[] = "\n};";
    

int check_reserved(char *line) {

    if ('A' <= line[0] && line[0] <='Z') {
	return 1;
    }

    return 0;
}


int decimal2binary(int decimal) {
    
    int binary = 0;
    int base = 10;
    int i = 0;

    binary = binary + ( decimal % 2 );
    decimal = decimal / 2;
    while (decimal > 0) {
	binary = binary + ( decimal % 2 ) * base;
	decimal = decimal / 2;
	base = base * 10;
	i++;
    }   

    return binary;
}



void main(int argc, char **argv) {
    
    char buf[MAXBUF];
    char outbuf[MAXBUF];
    int code;
    int binary;
    char* endp;
    int idx;
    char envelope[MAXBUF];
    int skip = 0;

    idx = 0;
    memset(buf, 0x00, MAXBUF);
    memset(outbuf, 0x00, MAXBUF);
    memset(envelope, 0x00, MAXBUF);

    FILE *in = fopen(FILENAME, "r");
    FILE *out = fopen(OUTPUT_FILENAME, "a+");

    sprintf(envelope, "/* %d %02x '' */", idx, idx);
    fwrite(header, sizeof(char), strlen(header), out);
    
    while (NULL != fgets(buf, MAXBUF, in)) {
	if (!check_reserved(buf)) {

	    if (skip) {
		skip = 0;
		fwrite(envelope, sizeof(char), strlen(envelope), out);
	    }
	    
	    code = (int)strtoul(buf, &endp, 16);
	    binary = decimal2binary(code);

	    sprintf(outbuf, "\t0x%02x, /* %08d */\n", code, binary);
	    fwrite(outbuf, sizeof(char), strlen(outbuf), out);

	    memset(buf, 0x00, MAXBUF);
	    memset(outbuf, 0x00, MAXBUF);
	    memset(envelope, 0x00, MAXBUF);
	    binary = 0;
	}
	else {
	    if (skip) {
	    }
	    else {
		fwrite("\n", sizeof(char), 1, out);
		skip = 1;

		sprintf(envelope, "\t/* %d 0x%02x '' */\n", idx, idx);		
		idx++;
	    }
	}
    }

    fwrite(footer, sizeof(char), strlen(footer), out);
    printf("idx: %d\n", idx);
    
}
