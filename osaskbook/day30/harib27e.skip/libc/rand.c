
#include "types.h"
#include "div64.h"


#define MAX (65536/2)
#define seed 1


#if 0
int rand() {

    static int r[MAX];
    static int i = 0;

    
    r[0] = seed;
    for (i=1; i<31; i++) {
//    r[i] = (16807LL * r[i-1]) % 2147483647;
	div_u64_rem((16807LL * r[i-1]), 2147483647, &r[i]);
	if (r[i] < 0) {
	    r[i] += 2147483647;
	}
    }
    for (i=31; i<34; i++) {
	r[i] = r[i-31];
    }
    for (i=34; i<344; i++) {
	r[i] = r[i-31] + r[i-3];
    }
    for (i=344; i<MAX; i++) {
	r[i] = r[i-31] + r[i-3];
//    printf("%d\n", ((unsigned int)r[i]) >> 1);
    }
    i++;

    return r[i];
  
}
#endif


unsigned long rand (void)
{
  static unsigned long rand;

  rand *= 1234567;
  rand += 1397;

  return rand;
}
