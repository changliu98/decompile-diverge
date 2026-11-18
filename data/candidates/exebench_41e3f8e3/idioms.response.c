void table_norm(double *data3, int data3_len, double *data2, int data2_len, int *result, int result_len)
{
  int i; int j;
  for (i = 0; i < data2_len; i++)
  {
    for (j = 0; j < data3_len; j++)
    {
      if (data3[j] > data2[i])
      {
        result[j]++;
      }
    }
  }
  for (i = 0; i < result_len; i++)
  {
    if (result[i] == 0)
    {
      result[i] = 1;
    }
  }
}