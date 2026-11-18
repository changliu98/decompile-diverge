void __cdecl mtxTranspose(float *mtx, const float *src)
{
  // Copy the main diagonal (elements at 0, 5, 10, 15 remain in place)
  mtx[0]  = src[0];
  mtx[5]  = src[5];
  mtx[10] = src[10];
  mtx[15] = src[15];

  // Swap symmetric off-diagonal elements
  mtx[1]  = src[4];
  mtx[4]  = src[1];

  mtx[2]  = src[8];
  mtx[8]  = src[2];

  mtx[3]  = src[12];
  mtx[12] = src[3];

  mtx[6]  = src[9];
  mtx[9]  = src[6];

  mtx[7]  = src[13];
  mtx[13] = src[7];

  mtx[11] = src[14];
  mtx[14] = src[11];
}