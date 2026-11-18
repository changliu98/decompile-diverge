int __cdecl func0(int n, int r, int p)
{
  _BYTE v4[4]; // [rsp+0h] [rbp-40h] BYREF
  int v5; // [rsp+4h] [rbp-3Ch]
  _DWORD *v6; // [rsp+8h] [rbp-38h]
  int j; // [rsp+14h] [rbp-2Ch]
  int i_0; // [rsp+18h] [rbp-28h]
  int i; // [rsp+1Ch] [rbp-24h]
  unsigned __int64 __vla_expr0; // [rsp+20h] [rbp-20h]
  _BYTE *v11; // [rsp+28h] [rbp-18h]
  int pa; // [rsp+34h] [rbp-Ch]
  int ra; // [rsp+38h] [rbp-8h]
  int na; // [rsp+3Ch] [rbp-4h]

  na = n;
  ra = r;
  pa = p;
  if ( r > n - r )
    ra = na - ra;
  v11 = v4;
  v6 = &v4[-((4LL * (unsigned int)(ra + 1) + 15) & 0xFFFFFFFFFFFFFFF0LL)];
  __vla_expr0 = (unsigned int)(ra + 1);
  for ( i = 0; i <= ra; ++i )
    v6[i] = 0;
  *v6 = 1;
  for ( i_0 = 1; i_0 <= na; ++i_0 )
  {
    if ( i_0 >= ra )
      v5 = ra;
    else
      v5 = i_0;
    for ( j = v5; j > 0; --j )
      v6[j] = (v6[j - 1] + v6[j]) % pa;
  }
  return v6[ra];
}