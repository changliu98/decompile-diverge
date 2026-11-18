void mtx3x3Transpose(float (*dest)[4][4], float (*src)[4][4])
{
  int i;
  int j;
  int k;
  int l;
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      for (k = 0; k < 4; k++)
      {
        for (l = 0; l < 4; l++)
        {
          dest[i][j][k][l] = src[i][j][k][l];
        }
      }
    }
  }
}