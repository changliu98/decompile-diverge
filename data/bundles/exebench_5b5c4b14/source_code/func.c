#include <math.h>

int jrand_(int *n, int *ix, int *iy, int *iz)
{

    int ret_val;


    static double u, x;
# 3867 "cstripack.c"
    *ix = *ix * 171 % 30269;
    *iy = *iy * 172 % 30307;
    *iz = *iz * 170 % 30323;
    x = (double) (*ix) / 30269. + (double) (*iy) / 30307. + (
     double) (*iz) / 30323.;
    u = x - (int) x;
    ret_val = (int) ((double) (*n) * u + 1.);
    return ret_val;
}
