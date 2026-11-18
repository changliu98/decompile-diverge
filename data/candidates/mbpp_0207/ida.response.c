int __cdecl func0(char *str)
{
  _BYTE v2[4]; // [rsp+0h] [rbp-50h] BYREF
  int v3; // [rsp+4h] [rbp-4Ch]
  unsigned __int64 v4; // [rsp+8h] [rbp-48h]
  _BYTE *v5; // [rsp+10h] [rbp-40h]
  int j_0; // [rsp+18h] [rbp-38h]
  int i_0; // [rsp+1Ch] [rbp-34h]
  int j; // [rsp+20h] [rbp-30h]
  int i; // [rsp+24h] [rbp-2Ch]
  unsigned __int64 __vla_expr1; // [rsp+28h] [rbp-28h]
  unsigned __int64 __vla_expr0; // [rsp+30h] [rbp-20h]
  _BYTE *v12; // [rsp+38h] [rbp-18h]
  int n; // [rsp+44h] [rbp-Ch]
  char *stra; // [rsp+48h] [rbp-8h]

  stra = str;
  n = strlen(str);
  v4 = (unsigned int)(n + 1);
  v12 = v2;
  v5 = &v2[-((4 * v4 * v4 + 15) & 0xFFFFFFFFFFFFFFF0LL)];
  __vla_expr0 = v4;
  __vla_expr1 = v4;
  for ( i = 0; i <= n; ++i )
  {
    for ( j = 0; j <= n; ++j )
      *(_DWORD *)&v5[4 * v4 * i + 4 * j] = 0;
  }
  for ( i_0 = 1; i_0 <= n; ++i_0 )
  {
    for ( j_0 = 1; j_0 <= n; ++j_0 )
    {
      if ( stra[i_0 - 1] != stra[j_0 - 1] || i_0 == j_0 )
      {
        if ( *(_DWORD *)&v5[4 * v4 * i_0 - 4 + 4 * j_0] <= *(_DWORD *)&v5[4 * v4 * (i_0 - 1) + 4 * j_0] )
          v3 = *(_DWORD *)&v5[4 * v4 * (i_0 - 1) + 4 * j_0];
        else
          v3 = *(_DWORD *)&v5[4 * v4 * i_0 - 4 + 4 * j_0];
        *(_DWORD *)&v5[4 * v4 * i_0 + 4 * j_0] = v3;
      }
      else
      {
        *(_DWORD *)&v5[4 * v4 * i_0 + 4 * j_0] = *(_DWORD *)&v5[4 * v4 * (i_0 - 1) - 4 + 4 * j_0] + 1;
      }
    }
  }
  return *(_DWORD *)&v5[4 * v4 * n + 4 * n];
}