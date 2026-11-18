int __cdecl transF(int xr, int xc, const float *xp, int tr, int tc, float *tp)
{
  int j; // [rsp+0h] [rbp-30h]
  int i; // [rsp+4h] [rbp-2Ch]

  if ( xr != tc || xc != tr )
    return 2000;
  for ( i = 0; i < tr; ++i )
  {
    for ( j = 0; j < tc; ++j )
      tp[j + tc * i] = xp[i + xc * j];
  }
  return 0;
}