int __cdecl func0(int *price, int n, int k)
{
  _BYTE v4[12]; // [rsp+0h] [rbp-60h] BYREF
  int v5; // [rsp+Ch] [rbp-54h]
  __int64 v6; // [rsp+10h] [rbp-50h]
  _BYTE *v7; // [rsp+18h] [rbp-48h]
  int curr_price; // [rsp+24h] [rbp-3Ch]
  int x; // [rsp+28h] [rbp-38h]
  int max_so_far; // [rsp+2Ch] [rbp-34h]
  int j; // [rsp+30h] [rbp-30h]
  int i; // [rsp+34h] [rbp-2Ch]
  unsigned __int64 __vla_expr1; // [rsp+38h] [rbp-28h]
  unsigned __int64 __vla_expr0; // [rsp+40h] [rbp-20h]
  _BYTE *v15; // [rsp+48h] [rbp-18h]
  int ka; // [rsp+50h] [rbp-10h]
  int na; // [rsp+54h] [rbp-Ch]
  int *pricea; // [rsp+58h] [rbp-8h]

  pricea = price;
  na = n;
  ka = k;
  v6 = (unsigned int)n;
  v15 = v4;
  v7 = &v4[-((4 * (unsigned int)n * (unsigned __int64)(unsigned int)(k + 1) + 15) & 0xFFFFFFFFFFFFFFF0LL)];
  __vla_expr0 = (unsigned int)(k + 1);
  __vla_expr1 = (unsigned int)n;
  for ( i = 0; i <= ka; ++i )
  {
    for ( j = 0; j < na; ++j )
    {
      if ( i && j )
      {
        max_so_far = 0;
        for ( x = 0; x < j; ++x )
        {
          curr_price = *(_DWORD *)&v7[4 * v6 * (i - 1) + 4 * x] + pricea[j] - pricea[x];
          if ( max_so_far < curr_price )
            max_so_far = curr_price;
        }
        if ( *(_DWORD *)&v7[4 * v6 * i - 4 + 4 * j] <= max_so_far )
          v5 = max_so_far;
        else
          v5 = *(_DWORD *)&v7[4 * v6 * i - 4 + 4 * j];
        *(_DWORD *)&v7[4 * v6 * i + 4 * j] = v5;
      }
      else
      {
        *(_DWORD *)&v7[4 * v6 * i + 4 * j] = 0;
      }
    }
  }
  return *(_DWORD *)&v7[4 * v6 * ka - 4 + 4 * na];
}