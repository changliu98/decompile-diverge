#include <math.h>

void grad1( int hash, float *gx ) {
    int h = hash & 15;
    *gx = 1.0f + (h & 7);
    if (h&8) *gx = - *gx;
    return;
}
