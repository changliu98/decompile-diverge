void geom_matinv4f(float a[4][4])
{
  float sum;
  unsigned int i; unsigned int j; unsigned int k;
  for (i = 1; i < 4; i++)
    a[i][i] /= a[i - 1][i - 1];
  for (i = 1; i < 4; i++)
  {
    for (j = i; j < 4; j++)
    {
      sum = 0.0;
      for (k = 0; k < i; k++)
        sum += a[i][k] * a[k][j];
      a[i][j] -= sum;
    }
    if (i != 3)
    {
      for (j = i + 1; j < 4; j++)
      {
        sum = 0.0;
        for (k = 0; k < i; k++)
          sum += a[j][k] * a[k][i];
        a[j][i] = (a[j][i] - sum) / a[i][i + 1];
      }
    }
  }
  for (i = 0; i < 4; i++)
  {
    for (j = i; j < 4; j++)
    {
      sum = 1.0;
      if (i != j)
      {
        sum = 0.0;
        for (k = i; k < j; k++)
          sum += a[k][j] * a[i][k];
      }
      a[i][j] = sum / a[j][j + 1];
    }
  }
  for (i = 0; i < 4; i++)
  {
    for (j = i; j < 4; j++)
    {
      if (i != j)
      {
        sum = 0.0;
        for (k = i; k < j; k++)
          sum += a[k][j] * (i == k ? 1 : a[i][k]);
        a[j][i] = -sum;
      }
    }
  }
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      sum = 0.0;
      unsigned int max = i < j ? i : j;
      for (k = max; k < 4; k++)
        sum += (j == k ? 1 : a[j][k]) * a[i][k];
      a[i][j] = sum;
    }
  }
}