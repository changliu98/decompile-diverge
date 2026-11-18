int __cdecl transF(int xr, int xc, const float *xp, int tr, int tc, float *tp)
{
  int i, j;

  // Check if the dimensions of the destination matrix (tr x tc) 
  // match the transposed dimensions of the source matrix (xc x xr)
  if (xr != tc || xc != tr)
    return 2000; // Dimension mismatch error code

  // Iterate through the rows of the destination matrix
  for (i = 0; i < tr; ++i)
  {
    // Iterate through the columns of the destination matrix
    for (j = 0; j < tc; ++j)
    {
      // Map 1D array pointers to 2D matrix indices:
      // tp[i][j] = xp[j][i]
      tp[i * tc + j] = xp[j * xc + i];
    }
  }
  
  return 0; // Success
}