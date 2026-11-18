void mtxLoadTranslate(float *mtx,float xTrans,float yTrans,float zTrans)

{
  float zTrans_local;
  float yTrans_local;
  float xTrans_local;
  float *mtx_local;
  
  mtx[0xf] = DAT_00102004;
  mtx[10] = DAT_00102004;
  mtx[5] = DAT_00102004;
  *mtx = DAT_00102004;
  mtx[0xb] = 0.0;
  mtx[9] = 0.0;
  mtx[8] = 0.0;
  mtx[7] = 0.0;
  mtx[6] = 0.0;
  mtx[4] = 0.0;
  mtx[3] = 0.0;
  mtx[2] = 0.0;
  mtx[1] = 0.0;
  mtx[0xc] = xTrans;
  mtx[0xd] = yTrans;
  mtx[0xe] = zTrans;
  return;
}