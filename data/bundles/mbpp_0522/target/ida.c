int __cdecl func0(int *arr, int n)
{
  __int64 v3; // [rsp+0h] [rbp-50h] BYREF
  _DWORD *v4; // [rsp+8h] [rbp-48h]
  _DWORD *v5; // [rsp+10h] [rbp-40h]
  int maximum; // [rsp+1Ch] [rbp-34h]
  int j; // [rsp+20h] [rbp-30h]
  int i; // [rsp+24h] [rbp-2Ch]
  unsigned __int64 __vla_expr1; // [rsp+28h] [rbp-28h]
  unsigned __int64 __vla_expr0; // [rsp+30h] [rbp-20h]
  __int64 *v11; // [rsp+38h] [rbp-18h]
  int na; // [rsp+44h] [rbp-Ch]
  int *arra; // [rsp+48h] [rbp-8h]

  arra = arr;
  na = n;
  v11 = &v3;
  v4 = (_DWORD *)((char *)&v3 - ((4LL * (unsigned int)(n + 1) + 15) & 0xFFFFFFFFFFFFFFF0LL));
  __vla_expr0 = (unsigned int)(n + 1);
  v5 = v4;
  __vla_expr1 = __vla_expr0;
  for ( i = 0; i <= na; ++i )
    v4[i] = 1;
  for ( i = 1; i < na; ++i )
  {
    for ( j = 0; j < i; ++j )
    {
      if ( arra[i] > arra[j] && v4[i] < v4[j] + 1 )
        v4[i] = v4[j] + 1;
    }
  }
  for ( i = 0; i <= na; ++i )
    v5[i] = 1;
  for ( i = na - 2; i >= 0; --i )
  {
    for ( j = na - 1; j > i; --j )
    {
      if ( arra[i] > arra[j] && v5[i] < v5[j] + 1 )
        v5[i] = v5[j] + 1;
    }
  }
  maximum = *v5 + *v4 - 1;
  for ( i = 1; i < na; ++i )
  {
    if ( v5[i] + v4[i] - 1 > maximum )
      maximum = v5[i] + v4[i] - 1;
  }
  return maximum;
}