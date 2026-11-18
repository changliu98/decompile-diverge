void __cdecl unscale(double *prob, unsigned int times)
{
  unsigned int i; // [rsp+0h] [rbp-10h]

  for ( i = 0; i < times; ++i )
    *prob = 8.636168555094445e-78 * *prob;
}