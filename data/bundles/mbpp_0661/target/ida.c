int __cdecl func0(int *arr, int n)
{
  int v3; // [rsp+0h] [rbp-50h] BYREF
  int v4; // [rsp+4h] [rbp-4Ch]
  int v5; // [rsp+8h] [rbp-48h]
  int v6; // [rsp+Ch] [rbp-44h]
  int v7; // [rsp+10h] [rbp-40h]
  int v8; // [rsp+14h] [rbp-3Ch]
  int *v9; // [rsp+18h] [rbp-38h]
  int max3; // [rsp+20h] [rbp-30h]
  int max2; // [rsp+24h] [rbp-2Ch]
  int max1; // [rsp+28h] [rbp-28h]
  int i; // [rsp+2Ch] [rbp-24h]
  unsigned __int64 __vla_expr0; // [rsp+30h] [rbp-20h]
  int *v15; // [rsp+38h] [rbp-18h]
  int na; // [rsp+44h] [rbp-Ch]
  int *arra; // [rsp+48h] [rbp-8h]

  arra = arr;
  na = n;
  v15 = &v3;
  v9 = (int *)((char *)&v3 - ((4LL * (unsigned int)n + 15) & 0xFFFFFFFFFFFFFFF0LL));
  __vla_expr0 = (unsigned int)n;
  if ( n >= 1 )
    *v9 = *arra;
  if ( na >= 2 )
    v9[1] = arra[1] + *arra;
  if ( na > 2 )
  {
    if ( v9[1] <= arra[2] + arra[1] )
      v8 = arra[2] + arra[1];
    else
      v8 = v9[1];
    if ( v8 <= arra[2] + *arra )
    {
      v6 = arra[2] + *arra;
    }
    else
    {
      if ( v9[1] <= arra[2] + arra[1] )
        v7 = arra[2] + arra[1];
      else
        v7 = v9[1];
      v6 = v7;
    }
    v9[2] = v6;
  }
  for ( i = 3; i < na; ++i )
  {
    max1 = v9[i - 1];
    max2 = arra[i] + v9[i - 2];
    max3 = v9[i - 3] + arra[i - 1] + arra[i];
    if ( max1 <= max2 )
      v5 = max2;
    else
      v5 = max1;
    if ( v5 <= max3 )
    {
      v3 = max3;
    }
    else
    {
      if ( max1 <= max2 )
        v4 = max2;
      else
        v4 = max1;
      v3 = v4;
    }
    v9[i] = v3;
  }
  return v9[na - 1];
}