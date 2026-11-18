#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <math.h>

#include <time.h>

int transF(int xr, int xc, const float* xp,int tr, int tc, float* tp) {
    do {if(!(xr==tc && xc==tr)) {do {return 2000;} while (0);}} while (0);
    ;
    int i,j;
    for (i=0; i<tr; i++) {
        for (j=0; j<tc; j++) {
        tp[i*tc+j] = xp[j*xc+i];
        }
    }
    return 0;
}
