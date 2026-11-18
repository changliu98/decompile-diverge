void __cdecl myGlMultMatrix(const float a[4][4], const float b[4][4], float out[4][4])
{
  int i, j;

  for (i = 0; i < 4; ++i)
  {
    for (j = 0; j < 4; ++j)
    {
      // Dot product of the i-th row of 'a' and the j-th column of 'b'
      out[i][j] = a[i][0] * b[0][j] 
                + a[i][1] * b[1][j] 
                + a[i][2] * b[2][j] 
                + a[i][3] * b[3][j];
    }
  }
}