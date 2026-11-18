int count_ones(int *array, int N, int P)
{
  int count = 0;
  int i;
  for (i = 0; i < N; i++)
    if ((array[i] * array[i]) % P == 1)
      count++;
  return (count);
}