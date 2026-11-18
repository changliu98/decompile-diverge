long __cdecl sort_omegas(double *v)
{
  double w; // [rsp+0h] [rbp-30h]
  double w_8; // [rsp+8h] [rbp-28h]
  __int64 w_8a; // [rsp+8h] [rbp-28h]
  double w_16; // [rsp+10h] [rbp-20h]
  double w_24; // [rsp+18h] [rbp-18h]
  long i; // [rsp+20h] [rbp-10h]

  i = 0LL;
  if ( *v <= v[1] )
  {
    w = *v;
    w_8 = v[1];
  }
  else
  {
    w = v[1];
    w_8 = *v;
    i = 1LL;
  }
  if ( v[2] <= v[3] )
  {
    w_16 = v[2];
    w_24 = v[3];
  }
  else
  {
    w_16 = v[3];
    w_24 = v[2];
  }
  if ( w <= w_16 )
  {
    *v = w;
    v[1] = w_16;
  }
  else
  {
    *v = w_16;
    v[1] = w;
    if ( !i )
      i = 4LL;
  }
  if ( w_8 <= w_24 )
  {
    v[3] = w_24;
    v[2] = w_8;
    if ( i == 1 )
      i = 5LL;
  }
  else
  {
    v[3] = w_8;
    v[2] = w_24;
    if ( i == 1 )
      i = 3LL;
  }
  if ( v[1] <= v[2] )
  {
    if ( i == 4 )
      i = 1LL;
    if ( i == 5 )
      return 2LL;
  }
  else
  {
    w_8a = *((_QWORD *)v + 1);
    v[1] = v[2];
    *((_QWORD *)v + 2) = w_8a;
    if ( i == 4 )
      i = 2LL;
    if ( i == 5 )
      return 1LL;
  }
  return i;
}