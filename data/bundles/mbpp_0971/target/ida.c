int __cdecl func0(int n, int a, int b, int c)
{
  _BYTE v5[4]; // [rsp+0h] [rbp-40h] BYREF
  int v6; // [rsp+4h] [rbp-3Ch]
  int v7; // [rsp+8h] [rbp-38h]
  int v8; // [rsp+Ch] [rbp-34h]
  _DWORD *v9; // [rsp+10h] [rbp-30h]
  int i_0; // [rsp+18h] [rbp-28h]
  int i; // [rsp+1Ch] [rbp-24h]
  unsigned __int64 __vla_expr0; // [rsp+20h] [rbp-20h]
  _BYTE *v13; // [rsp+28h] [rbp-18h]
  int ca; // [rsp+30h] [rbp-10h]
  int ba; // [rsp+34h] [rbp-Ch]
  int aa; // [rsp+38h] [rbp-8h]
  int na; // [rsp+3Ch] [rbp-4h]

  na = n;
  aa = a;
  ba = b;
  ca = c;
  v13 = v5;
  v9 = &v5[-((4LL * (unsigned int)(n + 10) + 15) & 0xFFFFFFFFFFFFFFF0LL)];
  __vla_expr0 = (unsigned int)(n + 10);
  for ( i = 0; i < na + 10; ++i )
    v9[i] = -1;
  *v9 = 0;
  for ( i_0 = 0; i_0 <= na; ++i_0 )
  {
    if ( v9[i_0] != -1 )
    {
      if ( aa + i_0 <= na )
      {
        if ( v9[i_0] + 1 <= v9[aa + i_0] )
          v8 = v9[aa + i_0];
        else
          v8 = v9[i_0] + 1;
        v9[aa + i_0] = v8;
      }
      if ( ba + i_0 <= na )
      {
        if ( v9[i_0] + 1 <= v9[ba + i_0] )
          v7 = v9[ba + i_0];
        else
          v7 = v9[i_0] + 1;
        v9[ba + i_0] = v7;
      }
      if ( ca + i_0 <= na )
      {
        if ( v9[i_0] + 1 <= v9[ca + i_0] )
          v6 = v9[ca + i_0];
        else
          v6 = v9[i_0] + 1;
        v9[ca + i_0] = v6;
      }
    }
  }
  return v9[na];
}