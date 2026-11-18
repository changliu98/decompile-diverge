void add_one(int *in, int size, int *out)
{
  int i;
  for (i = 0; i < size - 1; i++)
    out[i] = in[i] + in[i + 1];
}