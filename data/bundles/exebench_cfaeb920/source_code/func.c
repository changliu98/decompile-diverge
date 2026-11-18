#include <math.h>

#include <memory.h>

void mtxTranspose(float *mtx, const float *src) {


    float tmp;
    mtx[0] = src[0];
    mtx[5] = src[5];
    mtx[10] = src[10];
    mtx[15] = src[15];

    tmp = src[4];
    mtx[4] = src[1];
    mtx[1] = tmp;

    tmp = src[8];
    mtx[8] = src[2];
    mtx[2] = tmp;

    tmp = src[12];
    mtx[12] = src[3];
    mtx[3] = tmp;

    tmp = src[9];
    mtx[9] = src[6];
    mtx[6] = tmp;

    tmp = src[13];
    mtx[13] = src[7];
    mtx[ 7] = tmp;

    tmp = src[14];
    mtx[14] = src[11];
    mtx[11] = tmp;
}
