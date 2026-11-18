long __cdecl metric(double *x, double *y, double *z, double *M)
{
  // Initialize the 3x3 matrix M to the Identity matrix
  M[0] = 1.0;
  M[1] = 0.0;
  M[2] = 0.0;
  
  M[3] = 0.0;
  M[4] = 1.0;
  M[5] = 0.0;
  
  M[6] = 0.0;
  M[7] = 0.0;
  M[8] = 1.0;

  return 0LL;
}