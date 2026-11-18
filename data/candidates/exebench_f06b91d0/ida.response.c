void __cdecl add_vector(const double *a, const double *b, double *out)
{
  int i; // [rsp+0h] [rbp-1Ch]

  for ( i = 0; i < 3; ++i )
    out[i] = a[i] + b[i];
}