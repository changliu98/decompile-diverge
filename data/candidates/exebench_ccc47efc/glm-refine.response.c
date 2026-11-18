double __cdecl determinant_3x3(float *inp)
{
  double m[3][3];
  int i, j;

  // Initialize the 3x3 matrix from the input array
  for (i = 0; i < 3; ++i)
  {
    for (j = 0; j < 3; ++j)
      m[i][j] = inp[3 * j + i];
  }

  // Calculate the determinant using the cofactor expansion along the first row
  return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
       - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
       + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}