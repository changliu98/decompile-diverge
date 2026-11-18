void __cdecl mtxLoadIdentity(float *mtx)
{
  // Row 0
  mtx[0]  = 1.0;
  mtx[1]  = 0.0;
  mtx[2]  = 0.0;
  mtx[3]  = 0.0;

  // Row 1
  mtx[4]  = 0.0;
  mtx[5]  = 1.0;
  mtx[6]  = 0.0;
  mtx[7]  = 0.0;

  // Row 2
  mtx[8]  = 0.0;
  mtx[9]  = 0.0;
  mtx[10] = 1.0;
  mtx[11] = 0.0;

  // Row 3
  mtx[12] = 0.0;
  mtx[13] = 0.0;
  mtx[14] = 0.0;
  mtx[15] = 1.0;
}