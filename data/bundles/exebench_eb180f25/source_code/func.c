#include <stdlib.h>

double
Mat_doubleSwap( double *a )
{




    union {
        char a[8];
        double b;
    } tmp;

    tmp.b = *a;





    tmp.a[0]^=tmp.a[7];tmp.a[7]^=tmp.a[0];tmp.a[0]^=tmp.a[7];
    tmp.a[1]^=tmp.a[6];tmp.a[6]^=tmp.a[1];tmp.a[1]^=tmp.a[6];
    tmp.a[2]^=tmp.a[5];tmp.a[5]^=tmp.a[2];tmp.a[2]^=tmp.a[5];
    tmp.a[3]^=tmp.a[4];tmp.a[4]^=tmp.a[3];tmp.a[3]^=tmp.a[4];
# 255 "endian.c"
    *a = tmp.b;
    return *a;

}
