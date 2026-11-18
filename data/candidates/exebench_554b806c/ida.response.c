bool __cdecl is_empty(float *spectrum, int N)
{
  int k; // [rsp+0h] [rbp-18h]

  for ( k = 0; k <= N; ++k )
  {
    if ( spectrum[k] > 1.1754944e-38 )
      return 0;
  }
  return 1;
}