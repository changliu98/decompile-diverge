static double func0(int *data, int len)
{
  int i; int sum = 0;
  for (i = 0; i < len; i++)
    sum += data[i];
  return (double)sum / (double)len;
}