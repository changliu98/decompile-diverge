#include <math.h>

#include <memory.h>

void mtxLoadScale(float *mtx, float xScale, float yScale, float zScale) {




    mtx[ 0] = xScale;
    mtx[ 5] = yScale;
    mtx[10] = zScale;
    mtx[15] = 1.0f;

    mtx[ 1] = mtx[ 2] = mtx[ 3] = mtx[ 4] =
    mtx[ 6] = mtx[ 7] = mtx[ 8] = mtx[ 9] =
    mtx[11] = mtx[12] = mtx[13] = mtx[14] = 0.0;
}
