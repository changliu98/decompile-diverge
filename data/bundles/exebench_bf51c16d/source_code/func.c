#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <math.h>

#include <time.h>

int condF(int xn, float*xp,int yn, float*yp,int ltn, float*ltp,int eqn, float*eqp,int gtn, float*gtp,int rn, float*rp) {
    do {if(!(xn==yn && xn==ltn && xn==eqn && xn==gtn && xn==rn)) {do {return 2000;} while (0);}} while (0);
   
    int k;
    for(k=0;k<xn;k++) {
        rp[k] = xp[k]<yp[k]?ltp[k]:(xp[k]>yp[k]?gtp[k]:eqp[k]);
    }
    return 0;
}
