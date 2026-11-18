void matmult(float a[4][4], float b[4][4], float c[4][4])
{
  int i; int j; int k;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
    {
      c[i][j] = 0.0;
      for (k = 0; k < 4; k++)
        c[i][j] += a[k][i]*b[j][k];
    }
}