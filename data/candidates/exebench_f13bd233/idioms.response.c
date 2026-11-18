void mtxLoadTranslate(float mtx[16], float xTrans, float yTrans, float zTrans)
{
  mtx[15] = 1.0f;
  mtx[10] = 1.0f;
  mtx[5] = 1.0f;
  mtx[0] = 1.0f;
  mtx[11] = 0.0f;
  mtx[9] = 0.0f;
  mtx[8] = 0.0f;
  mtx[7] = 0.0f;
  mtx[6] = 0.0f;
  mtx[4] = 0.0f;
  mtx[3] = 0.0f;
  mtx[2] = 0.0f;
  mtx[1] = 0.0f;
  mtx[12] = xTrans;
  mtx[13] = yTrans;
  mtx[14] = zTrans;
}