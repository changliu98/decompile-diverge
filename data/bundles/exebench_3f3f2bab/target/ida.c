int __cdecl sboxCHECK(float *lb, float *ub, int m)
{
  int i; // [rsp+0h] [rbp-20h]

  if ( !lb || !ub )
    return 1;
  for ( i = 0; i < m; ++i )
  {
    if ( lb[i] > ub[i] )
      return 0;
  }
  return 1;
}