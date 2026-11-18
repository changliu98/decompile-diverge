void mtxLoadIdentity(float *mtx)

{
  float *mtx_local;
  
  mtx[0xf] = DAT_00102004;
  mtx[10] = DAT_00102004;
  mtx[5] = DAT_00102004;
  *mtx = DAT_00102004;
  mtx[0xe] = 0.0;
  mtx[0xd] = 0.0;
  mtx[0xc] = 0.0;
  mtx[0xb] = 0.0;
  mtx[9] = 0.0;
  mtx[8] = 0.0;
  mtx[7] = 0.0;
  mtx[6] = 0.0;
  mtx[4] = 0.0;
  mtx[3] = 0.0;
  mtx[2] = 0.0;
  mtx[1] = 0.0;
  return;
}