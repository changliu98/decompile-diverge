void mtxScaleMatrix(float *mtx,float xScale,float yScale,float zScale)

{
  float zScale_local;
  float yScale_local;
  float xScale_local;
  float *mtx_local;
  
  *mtx = xScale * *mtx;
  mtx[4] = xScale * mtx[4];
  mtx[8] = xScale * mtx[8];
  mtx[0xc] = xScale * mtx[0xc];
  mtx[1] = yScale * mtx[1];
  mtx[5] = yScale * mtx[5];
  mtx[9] = yScale * mtx[9];
  mtx[0xd] = yScale * mtx[0xd];
  mtx[2] = zScale * mtx[2];
  mtx[6] = zScale * mtx[6];
  mtx[10] = zScale * mtx[10];
  mtx[0xe] = zScale * mtx[0xe];
  return;
}