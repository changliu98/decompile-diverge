void mtxTranspose(float *mtx,float *src)

{
  float fVar1;
  float tmp;
  float *src_local;
  float *mtx_local;
  
  *mtx = *src;
  mtx[5] = src[5];
  mtx[10] = src[10];
  mtx[0xf] = src[0xf];
  fVar1 = src[4];
  mtx[4] = src[1];
  mtx[1] = fVar1;
  fVar1 = src[8];
  mtx[8] = src[2];
  mtx[2] = fVar1;
  fVar1 = src[0xc];
  mtx[0xc] = src[3];
  mtx[3] = fVar1;
  fVar1 = src[9];
  mtx[9] = src[6];
  mtx[6] = fVar1;
  fVar1 = src[0xd];
  mtx[0xd] = src[7];
  mtx[7] = fVar1;
  fVar1 = src[0xe];
  mtx[0xe] = src[0xb];
  mtx[0xb] = fVar1;
  return;
}