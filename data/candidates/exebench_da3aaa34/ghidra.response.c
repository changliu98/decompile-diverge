void mtxLoadScale(float *mtx,float xScale,float yScale,float zScale)

{
  float zScale_local;
  float yScale_local;
  float xScale_local;
  float *mtx_local;
  
  *mtx = xScale;
  mtx[5] = yScale;
  mtx[10] = zScale;
  mtx[0xf] = DAT_00102004;
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