int __cdecl func0(int *arr, int n)
{
  __int64 v3; // [rsp+0h] [rbp-60h] BYREF
  __int64 v4; // [rsp+8h] [rbp-58h]
  int i_3; // [rsp+14h] [rbp-4Ch]
  int max_sum; // [rsp+18h] [rbp-48h]
  int j_0; // [rsp+1Ch] [rbp-44h]
  int i_2; // [rsp+20h] [rbp-40h]
  int i_1; // [rsp+24h] [rbp-3Ch]
  unsigned __int64 __vla_expr1; // [rsp+28h] [rbp-38h]
  int j; // [rsp+34h] [rbp-2Ch]
  int i_0; // [rsp+38h] [rbp-28h]
  int i; // [rsp+3Ch] [rbp-24h]
  unsigned __int64 __vla_expr0; // [rsp+40h] [rbp-20h]
  __int64 *v15; // [rsp+48h] [rbp-18h]
  int na; // [rsp+54h] [rbp-Ch]
  int *arra; // [rsp+58h] [rbp-8h]
  __int64 savedregs; // [rsp+60h] [rbp+0h] BYREF

  arra = arr;
  na = n;
  v15 = &v3;
  v4 = (__int64)&v3 - ((4LL * (unsigned int)n + 15) & 0xFFFFFFFFFFFFFFF0LL);
  __vla_expr0 = (unsigned int)n;
  for ( i = 0; i < na; ++i )
    *(_DWORD *)(v4 + 4LL * i) = arra[i];
  for ( i_0 = 1; i_0 < na; ++i_0 )
  {
    for ( j = 0; j < i_0; ++j )
    {
      if ( arra[i_0] > arra[j] && *(_DWORD *)(v4 + 4LL * i_0) < arra[i_0] + *(_DWORD *)(v4 + 4LL * j) )
        *(_DWORD *)(v4 + 4LL * i_0) = arra[i_0] + *(_DWORD *)(v4 + 4LL * j);
    }
  }
  v3 = (__int64)&savedregs - ((4LL * (unsigned int)na + 15) & 0xFFFFFFFFFFFFFFF0LL);
  __vla_expr1 = (unsigned int)na;
  for ( i_1 = 0; i_1 < na; ++i_1 )
    *(_DWORD *)(v3 + 4LL * i_1) = arra[i_1];
  for ( i_2 = 1; i_2 < na; ++i_2 )
  {
    for ( j_0 = 0; j_0 < i_2; ++j_0 )
    {
      if ( arra[na - i_2 - 1] > arra[na - j_0 - 1]
        && *(_DWORD *)(v3 + 4LL * (na - i_2 - 1)) < arra[na - i_2 - 1] + *(_DWORD *)(v3 + 4LL * (na - j_0 - 1)) )
      {
        *(_DWORD *)(v3 + 4LL * (na - i_2 - 1)) = arra[na - i_2 - 1] + *(_DWORD *)(v3 + 4LL * (na - j_0 - 1));
      }
    }
  }
  max_sum = -99999999;
  for ( i_3 = 0; i_3 < na; ++i_3 )
  {
    if ( max_sum < *(_DWORD *)(v3 + 4LL * i_3) + *(_DWORD *)(v4 + 4LL * i_3) - arra[i_3] )
      max_sum = *(_DWORD *)(v3 + 4LL * i_3) + *(_DWORD *)(v4 + 4LL * i_3) - arra[i_3];
  }
  return max_sum;
}