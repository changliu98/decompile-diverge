void __cdecl func0(const float *xs, int xs_size, float *out)
{
  int i; // [rsp+0h] [rbp-1Ch]

  for ( i = 1; i < xs_size; ++i )
    out[i - 1] = (float)i * xs[i];
}