void mtx3x3Transpose(float *mtx,float *src)

{
  float fVar1;
  float tmp;
  float *src_local;
  float *mtx_local;
  
  *mtx = *src;
  mtx[4] = src[4];
  mtx[8] = src[8];
  fVar1 = src[1];
  mtx[1] = src[3];
  mtx[3] = fVar1;
  fVar1 = src[2];
  mtx[2] = src[6];
  mtx[6] = fVar1;
  fVar1 = src[5];
  mtx[5] = src[7];
  mtx[7] = fVar1;
  return;
}