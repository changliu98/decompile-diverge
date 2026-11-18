void mtxScaleMatrix(float *mtx, float xScale, float yScale, float zScale) {





    mtx[ 0] *= xScale;
    mtx[ 4] *= xScale;
    mtx[ 8] *= xScale;
    mtx[12] *= xScale;

    mtx[ 1] *= yScale;
    mtx[ 5] *= yScale;
    mtx[ 9] *= yScale;
    mtx[13] *= yScale;

    mtx[ 2] *= zScale;
    mtx[ 6] *= zScale;
    mtx[10] *= zScale;
    mtx[14] *= zScale;
}