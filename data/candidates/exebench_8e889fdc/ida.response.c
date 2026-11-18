void __cdecl load_scl_mat(float *M, float x, float y, float z)
{
  *M = x;
  M[4] = 0.0;
  M[8] = 0.0;
  M[12] = 0.0;
  M[1] = 0.0;
  M[5] = y;
  M[9] = 0.0;
  M[13] = 0.0;
  M[2] = 0.0;
  M[6] = 0.0;
  M[10] = z;
  M[14] = 0.0;
  M[3] = 0.0;
  M[7] = 0.0;
  M[11] = 0.0;
  M[15] = 1.0;
}