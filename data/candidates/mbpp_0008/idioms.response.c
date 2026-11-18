void func0(int *in, int *out, int size)
{
  int i;
  for (i = 0; i < size; i++)
    out[i] = in[i] * in[i];
}