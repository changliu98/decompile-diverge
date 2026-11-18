int __cdecl func0(int *arr, int n)
{
  __int64 v3; // [rsp+0h] [rbp-40h] BYREF
  int i_1; // [rsp+Ch] [rbp-34h]
  int maximum; // [rsp+10h] [rbp-30h]
  int j; // [rsp+14h] [rbp-2Ch]
  int i_0; // [rsp+18h] [rbp-28h]
  int i; // [rsp+1Ch] [rbp-24h]
  unsigned __int64 __vla_expr0; // [rsp+20h] [rbp-20h]
  __int64 *v10; // [rsp+28h] [rbp-18h]
  int na; // [rsp+34h] [rbp-Ch]
  int *arra; // [rsp+38h] [rbp-8h]

  arra = arr;
  na = n;
  v10 = &v3;
  v3 = (__int64)&v3 - ((4LL * (unsigned int)n + 15) & 0xFFFFFFFFFFFFFFF0LL);
  __vla_expr0 = (unsigned int)n;
  for ( i = 0; i < na; ++i )
    *(_DWORD *)(v3 + 4LL * i) = 1;
  for ( i_0 = 1; i_0 < na; ++i_0 )
  {
    for ( j = 0; j < i_0; ++j )
    {
      if ( arra[i_0] > arra[j] && *(_DWORD *)(v3 + 4LL * i_0) < *(_DWORD *)(v3 + 4LL * j) + 1 )
        *(_DWORD *)(v3 + 4LL * i_0) = *(_DWORD *)(v3 + 4LL * j) + 1;
    }
  }
  maximum = 0;
  for ( i_1 = 0; i_1 < na; ++i_1 )
  {
    if ( *(_DWORD *)(v3 + 4LL * i_1) > maximum )
      maximum = *(_DWORD *)(v3 + 4LL * i_1);
  }
  return maximum;
}