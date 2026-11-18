void matmul(float a[4][4], float b[4][4], float out[4][4])
{
  int i; int j;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      out[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j] + a[i][3] * b[3][j];
}