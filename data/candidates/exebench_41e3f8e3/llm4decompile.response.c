void table_norm(double *data3_nn, int data3_len, double *data2_nn, int data2_len, long *result, int result_len)
{
  int i, j;
  for (i = 0; i < data2_len; i++)
    for (j = 0; j < data3_len; j++)
      if (data3_nn[j] < data2_nn[i])
        result[j]++;

  for (i = 0; i < result_len; i++)
    if (result[i] == 0)
      result[i] = 1;
}