void mm_us(float a[4][4], float b[4][4], float c[4][4])
{
  int i; int j; int k;
  float sum;
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      sum = 0.0;
      for (k = 0; k < 4; k++)
      {
        sum += a[i][k] * b[k][j];
      }
      c[i][j] = sum;
    }
  }
}