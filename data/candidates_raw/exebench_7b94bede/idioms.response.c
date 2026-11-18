void copy(float a[4][4], float b[4][4])
{
  unsigned int i; unsigned int j;
  for (j = 0; j < 4; j++)
    for (i = 0; i < 4; i++)
      b[j][i] = a[i][j];
}