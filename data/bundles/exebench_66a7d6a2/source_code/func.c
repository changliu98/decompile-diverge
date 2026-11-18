#include <stdlib.h>

void swapdouble(double *dbl)
{

    int t;
    int *dd = (int *)dbl;
    t = ((((unsigned int)dd[0]) & 0xff) << 24 | (((unsigned int)dd[0]) & 0xff00) << 8 | (((unsigned int)dd[0]) & 0xff0000) >> 8 | (((unsigned int)dd[0]) & 0xff000000) >> 24);
    dd[0] = ((((unsigned int)dd[1]) & 0xff) << 24 | (((unsigned int)dd[1]) & 0xff00) << 8 | (((unsigned int)dd[1]) & 0xff0000) >> 8 | (((unsigned int)dd[1]) & 0xff000000) >> 24);
    dd[1] = t;
}
