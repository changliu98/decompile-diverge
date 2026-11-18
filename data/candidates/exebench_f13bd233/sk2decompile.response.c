void mtxLoadTranslate(float *mtx, float x, float y, float z) {
  mtx[0] = 1.0f;
  mtx[5] = 1.0f;
  mtx[10] = 1.0f;
  mtx[15] = 1.0f;
  mtx[1] = 0.0f;
  mtx[2] = 0.0f;
  mtx[3] = 0.0f;
  mtx[4] = 0.0f;
  mtx[6] = 0.0f;
  mtx[7] = 0.0f;
  mtx[8] = 0.0f;
  mtx[9] = 0.0f;
  mtx[11] = 0.0f;
  mtx[12] = x;
  mtx[13] = y;
  mtx[14] = z;
}