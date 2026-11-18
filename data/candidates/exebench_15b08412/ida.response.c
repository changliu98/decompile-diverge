int __cdecl div_dbl(unsigned __int64 *u, unsigned __int64 v)
{
  unsigned __int128 v2; // rtt

  if ( !v || u[1] >= v )
    return 1;
  v2 = *(_OWORD *)u;
  *u = *(_OWORD *)u / v;
  u[1] = v2 % v;
  return 0;
}