int __cdecl func0(int *arr, int n, int k)
{
  __int64 v4; // [rsp+0h] [rbp-50h] BYREF
  unsigned __int64 v5; // [rsp+8h] [rbp-48h]
  __int64 v6; // [rsp+10h] [rbp-40h]
  int j_0; // [rsp+18h] [rbp-38h]
  int i_0; // [rsp+1Ch] [rbp-34h]
  int j; // [rsp+20h] [rbp-30h]
  int i; // [rsp+24h] [rbp-2Ch]
  unsigned __int64 __vla_expr1; // [rsp+28h] [rbp-28h]
  unsigned __int64 __vla_expr0; // [rsp+30h] [rbp-20h]
  __int64 *v13; // [rsp+38h] [rbp-18h]
  int ka; // [rsp+40h] [rbp-10h]
  int na; // [rsp+44h] [rbp-Ch]
  int *arra; // [rsp+48h] [rbp-8h]

  arra = arr;
  na = n;
  ka = k;
  v5 = (unsigned int)(n + 1);
  v13 = &v4;
  v6 = (__int64)&v4 - ((4 * v5 * (unsigned int)(k + 1) + 15) & 0xFFFFFFFFFFFFFFF0LL);
  __vla_expr0 = (unsigned int)(k + 1);
  __vla_expr1 = v5;
  for ( i = 0; i <= ka; ++i )
  {
    for ( j = 0; j <= na; ++j )
      *(_DWORD *)(4 * v5 * i + v6 + 4LL * j) = 0;
  }
  for ( i_0 = 1; i_0 <= ka; ++i_0 )
  {
    for ( j_0 = 1; j_0 <= na; ++j_0 )
    {
      *(_DWORD *)(4 * v5 * i_0 + v6 + 4LL * j_0) = *(_DWORD *)(4 * v5 * i_0 + v6 + 4LL * (j_0 - 1));
      if ( arra[j_0 - 1] <= i_0 && arra[j_0 - 1] > 0 )
        *(_DWORD *)(4 * v5 * i_0 + v6 + 4LL * j_0) += *(_DWORD *)(4 * v5 * (i_0 / arra[j_0 - 1]) + v6 + 4LL * (j_0 - 1))
                                                    + 1;
    }
  }
  return *(_DWORD *)(4 * v5 * ka + v6 + 4LL * na);
}