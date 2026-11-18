void __cdecl func0(const float *xs, int xs_size, float *out)
{
  for (int i = 1; i < xs_size; ++i)
  {
    out[i - 1] = (float)i * xs[i];
  }
}