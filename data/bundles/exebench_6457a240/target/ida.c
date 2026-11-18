void __cdecl peneira(int m, int *v)
{
  int t; // [rsp+0h] [rbp-1Ch]
  int f; // [rsp+4h] [rbp-18h]
  int p; // [rsp+8h] [rbp-14h]

  p = 1;
  f = 2;
  t = v[1];
  while ( f <= m )
  {
    if ( f < m && v[f] < v[f + 1] )
      ++f;
    if ( t >= v[f] )
      break;
    v[p] = v[f];
    p = f;
    f *= 2;
  }
  v[p] = t;
}