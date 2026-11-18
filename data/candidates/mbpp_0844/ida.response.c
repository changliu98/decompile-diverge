int __cdecl func0(int n, int k)
{
  __int64 v3; // [rsp+0h] [rbp-30h] BYREF
  int even; // [rsp+Ch] [rbp-24h]
  int odd; // [rsp+10h] [rbp-20h]
  int i; // [rsp+14h] [rbp-1Ch]
  unsigned __int64 __vla_expr0; // [rsp+18h] [rbp-18h]
  __int64 *v8; // [rsp+20h] [rbp-10h]
  int ka; // [rsp+28h] [rbp-8h]
  int na; // [rsp+2Ch] [rbp-4h]

  na = n;
  ka = k;
  v8 = &v3;
  v3 = (__int64)&v3 - ((4LL * (unsigned int)n + 15) & 0xFFFFFFFFFFFFFFF0LL);
  __vla_expr0 = (unsigned int)n;
  i = 0;
  for ( odd = 1; odd <= na; odd += 2 )
    *(_DWORD *)(v3 + 4LL * i++) = odd;
  for ( even = 2; even <= na; even += 2 )
    *(_DWORD *)(v3 + 4LL * i++) = even;
  return *(_DWORD *)(v3 + 4LL * (ka - 1));
}