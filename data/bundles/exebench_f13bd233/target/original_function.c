void mtxLoadTranslate(float *mtx, float xTrans, float yTrans, float zTrans) {





    mtx[ 0] = mtx[ 5] = mtx[10] = mtx[15] = 1.0f;

    mtx[ 1] = mtx[ 2] = mtx[ 3] = mtx[ 4] =
    mtx[ 6] = mtx[ 7] = mtx[ 8] = mtx[ 9] =
    mtx[11] = 0.0;

    mtx[12] = xTrans;
    mtx[13] = yTrans;
    mtx[14] = zTrans;
}