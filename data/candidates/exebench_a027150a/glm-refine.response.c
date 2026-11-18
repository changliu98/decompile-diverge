void __cdecl mtx3x3Transpose(float *mtx, const float *src)
{
  mtx[0] = src[0];
  mtx[4] = src[4];
  mtx[8] = src[8];

  mtx[1] = src[3];
  mtx[3] = src[1];

  mtx[2] = src[6];
  mtx[6] = src[2];

  mtx[5] = src[7];
  mtx[7] = src[5];
}