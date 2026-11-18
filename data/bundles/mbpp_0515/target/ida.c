bool __cdecl func0(int *arr, int n, int m)
{
  __int64 v4; // [rsp+0h] [rbp-70h] BYREF
  __int64 v5; // [rsp+8h] [rbp-68h]
  _BYTE *v6; // [rsp+10h] [rbp-60h]
  int j_0; // [rsp+1Ch] [rbp-54h]
  int j; // [rsp+20h] [rbp-50h]
  int k; // [rsp+24h] [rbp-4Ch]
  unsigned __int64 __vla_expr1; // [rsp+28h] [rbp-48h]
  __int64 *v11; // [rsp+30h] [rbp-40h]
  int v12; // [rsp+3Ch] [rbp-34h]
  int i_0; // [rsp+40h] [rbp-30h]
  int i; // [rsp+44h] [rbp-2Ch]
  unsigned __int64 __vla_expr0; // [rsp+48h] [rbp-28h]
  __int64 *v16; // [rsp+50h] [rbp-20h]
  int ma; // [rsp+58h] [rbp-18h]
  int na; // [rsp+5Ch] [rbp-14h]
  int *arra; // [rsp+60h] [rbp-10h]
  bool v20; // [rsp+6Fh] [rbp-1h]

  arra = arr;
  na = n;
  ma = m;
  if ( n > m )
    return 1;
  v16 = &v4;
  v6 = (char *)&v4 - (((unsigned int)ma + 15LL) & 0xFFFFFFFFFFFFFFF0LL);
  __vla_expr0 = (unsigned int)ma;
  for ( i = 0; i < ma; ++i )
    v6[i] = 0;
  for ( i_0 = 0; i_0 < na; ++i_0 )
  {
    if ( (*v6 & 1) != 0 )
    {
      v20 = 1;
      v12 = 1;
      return v20;
    }
    v11 = &v4;
    v5 = (__int64)&v4 - (((unsigned int)ma + 15LL) & 0xFFFFFFFFFFFFFFF0LL);
    __vla_expr1 = (unsigned int)ma;
    for ( k = 0; k < ma; ++k )
      *(_BYTE *)(v5 + k) = 0;
    for ( j = 0; j < ma; ++j )
    {
      if ( (v6[j] & 1) != 0 && (v6[(arra[i_0] + j) % ma] & 1) == 0 )
        *(_BYTE *)(v5 + (arra[i_0] + j) % ma) = 1;
    }
    for ( j_0 = 0; j_0 < ma; ++j_0 )
    {
      if ( (*(_BYTE *)(v5 + j_0) & 1) != 0 )
        v6[j_0] = 1;
    }
    v6[arra[i_0] % ma] = 1;
  }
  v20 = *v6 & 1;
  v12 = 1;
  return v20;
}