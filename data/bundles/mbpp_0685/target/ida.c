int __cdecl func0(int n)
{
  __int64 v2; // [rsp+0h] [rbp-40h] BYREF
  __int64 v3; // [rsp+8h] [rbp-38h]
  int i_0; // [rsp+14h] [rbp-2Ch]
  int sum; // [rsp+18h] [rbp-28h]
  int i; // [rsp+1Ch] [rbp-24h]
  int p; // [rsp+20h] [rbp-20h]
  int j; // [rsp+24h] [rbp-1Ch]
  unsigned __int64 __vla_expr0; // [rsp+28h] [rbp-18h]
  __int64 *v10; // [rsp+30h] [rbp-10h]
  int na; // [rsp+3Ch] [rbp-4h]

  na = n;
  v10 = &v2;
  v3 = (__int64)&v2 - (((unsigned int)(n + 1) + 15LL) & 0xFFFFFFFFFFFFFFF0LL);
  __vla_expr0 = (unsigned int)(n + 1);
  for ( j = 0; j <= na; ++j )
    *(_BYTE *)(v3 + j) = 1;
  for ( p = 2; p * p <= na; ++p )
  {
    if ( (*(_BYTE *)(v3 + p) & 1) == 1 )
    {
      for ( i = 2 * p; i <= na; i += p )
        *(_BYTE *)(v3 + i) = 0;
    }
  }
  sum = 0;
  for ( i_0 = 2; i_0 <= na; ++i_0 )
  {
    if ( (*(_BYTE *)(v3 + i_0) & 1) != 0 )
      sum += i_0;
  }
  return sum;
}