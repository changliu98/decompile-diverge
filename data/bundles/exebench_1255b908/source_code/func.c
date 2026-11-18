#include <stdlib.h>

#include <string.h>

#include <stdio.h>

#include <math.h>

static int clip_wh(int *x, int *width, const int min_width, const int max_width)
{


    if(*x < min_width) {
 const int xoff = min_width - (*x);

 *width += *x;
 *x = min_width;
 return xoff;
    } else if(*x + *width >= max_width) {
 *width = max_width - *x;
    }
    return 0;
}
