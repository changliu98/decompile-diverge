void __cdecl mtxLoadTranslate(float *mtx, float xTrans, float yTrans, float zTrans)
{
  mtx[15] = 1.0;
  mtx[10] = 1.0;
  mtx[5] = 1.0;
  *mtx = 1.0;
  mtx[11] = 0.0;
  mtx[9] = 0.0;
  mtx[8] = 0.0;
  mtx[7] = 0.0;
  mtx[6] = 0.0;
  mtx[4] = 0.0;
  mtx[3] = 0.0;
  mtx[2] = 0.0;
  mtx[1] = 0.0;
  mtx[12] = xTrans;
  mtx[13] = yTrans;
  mtx[14] = zTrans;
}