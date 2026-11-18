void func0(float *in, int size, float *out)
{
  int i; int j;
  int even_count;
  float *even;
  float temp;
  even = (float *)malloc((size / 2 + 1) * sizeof(float));
  even_count = 0;
  for (i = 0; i < size; i += 2)
    even[even_count++] = in[i];
  for (i = 0; i < even_count - 1; i++)
  {
    for (j = 0; j < even_count - i - 1; j++)
    {
      if (even[j] > even[j + 1])
      {
        temp = even[j];
        even[j] = even[j + 1];
        even[j + 1] = temp;
      }
    }
  }
  for (i = 0; i < size; i++)
    out[i] = (i % 2 == 0 ? even[i / 2] : in[i]);
  free(even);
}