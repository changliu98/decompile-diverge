void mtxScaleMatrix(float *mtx, float x, float y, float z) {
  mtx[0] *= x;
  mtx[4] *= x;
  mtx[8] *= x;
  mtx[12] *= x;
  mtx[1] *= y;
  mtx[5] *= y;
  mtx[9] *= y;
  mtx[13] *= y;
  mtx[2] *= z;
  mtx[6] *= z;
  mtx[10] *= z;
  mtx[14] *= z;
}