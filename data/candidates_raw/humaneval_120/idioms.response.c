void kth_largest(int *in, int in_size, int k, int *out)
{
  int i; int j;
  int temp;
  for (i = 0; i < in_size - 1; i++)
  {
    for (j = 0; j < in_size - i - 1; j++)
    {
      if (in[j] > in[j + 1])
      {
        temp = in[j];
        in[j] = in[j + 1];
        in[j + 1] = temp;
      }
    }
  }
  for (i = 0; i < k; i++)
  {
    out[i] = in[in_size - k + i];
  }
}