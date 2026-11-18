int *unique(int *in, int size, int *out_size)
{
  int *out = (int*)malloc(size * sizeof(int));
  int i;
  int j;
  int found;
  int out_count = 0;
  for (i = 0; i < size; i++)
  {
    found = 0;
    for (j = 0; j < out_count; j++)
    {
      if (in[i] == out[j])
      {
        found = 1;
        break;
      }
    }
    if (!found)
    {
      out[out_count++] = in[i];
    }
  }
  for (i = 0; i < out_count - 1; i++)
  {
    for (j = i + 1; j < out_count; j++)
    {
      if (out[i] > out[j])
      {
        int temp = out[i];
        out[i] = out[j];
        out[j] = temp;
      }
    }
  }
  *out_size = out_count;
  return out;
}