void func0(float *xs, int xs_size, float *out)
{
  int i;
  for (i = 1; i < xs_size; i++)
    out[i - 1] = xs[i] * i;
}