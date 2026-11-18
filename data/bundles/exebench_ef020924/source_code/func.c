#include <stdlib.h>

void swapfloat(float *flt)
{

    int *ff = (int *)flt;
    ff[0] = ((((unsigned int)ff[0]) & 0xff) << 24 | (((unsigned int)ff[0]) & 0xff00) << 8 | (((unsigned int)ff[0]) & 0xff0000) >> 8 | (((unsigned int)ff[0]) & 0xff000000) >> 24);
}
