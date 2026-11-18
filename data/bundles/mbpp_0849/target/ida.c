int __cdecl func0(int N)
{
  __int64 v2; // [rsp+0h] [rbp-30h] BYREF
  int j; // [rsp+Ch] [rbp-24h]
  int i_0; // [rsp+10h] [rbp-20h]
  int i; // [rsp+14h] [rbp-1Ch]
  unsigned __int64 __vla_expr0; // [rsp+18h] [rbp-18h]
  __int64 *v7; // [rsp+20h] [rbp-10h]
  int Na; // [rsp+2Ch] [rbp-4h]

  Na = N;
  v7 = &v2;
  v2 = (__int64)&v2 - ((4LL * (unsigned int)(N + 1) + 15) & 0xFFFFFFFFFFFFFFF0LL);
  __vla_expr0 = (unsigned int)(N + 1);
  for ( i = 0; i <= Na; ++i )
    *(_DWORD *)(v2 + 4LL * i) = 0;
  for ( i_0 = 2; i_0 <= Na; ++i_0 )
  {
    if ( !*(_DWORD *)(v2 + 4LL * i_0) )
    {
      for ( j = i_0; j <= Na; j += i_0 )
        *(_DWORD *)(v2 + 4LL * j) += i_0;
    }
  }
  return *(_DWORD *)(v2 + 4LL * Na);
}