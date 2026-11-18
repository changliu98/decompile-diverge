void __cdecl numpar(double *param, int *len, int *out)
{
  unsigned __int64 v3; // rax
  __int64 v4; // [rsp+0h] [rbp-50h] BYREF
  double diff; // [rsp+8h] [rbp-48h]
  int count; // [rsp+14h] [rbp-3Ch]
  unsigned __int64 __vla_expr0; // [rsp+18h] [rbp-38h]
  __int64 *v8; // [rsp+20h] [rbp-30h]
  int k; // [rsp+2Ch] [rbp-24h]
  int j; // [rsp+30h] [rbp-20h]
  int i; // [rsp+34h] [rbp-1Ch]
  int *outa; // [rsp+38h] [rbp-18h]
  int *lena; // [rsp+40h] [rbp-10h]
  double *parama; // [rsp+48h] [rbp-8h]

  parama = param;
  lena = len;
  outa = out;
  i = -1;
  j = 0;
  k = 0;
  v3 = (unsigned int)*len;
  v8 = &v4;
  v4 = (__int64)&v4 - ((4 * v3 + 15) & 0xFFFFFFFFFFFFFFF0LL);
  __vla_expr0 = v3;
  count = -1;
  diff = 0.0;
  while ( i < *lena - 1 )
  {
    ++i;
    for ( j = 0; j < count; ++j )
    {
      if ( i == *(_DWORD *)(v4 + 4LL * j) )
        ++i;
    }
    for ( k = i + 1; k < *lena; ++k )
    {
      for ( j = 0; j < count; ++j )
      {
        if ( k == *(_DWORD *)(v4 + 4LL * j) )
          ++k;
      }
      diff = parama[i] - parama[k];
      if ( diff < 0.0 )
        diff = -1.0 * diff;
      if ( diff == 0.0 )
      {
        *(_DWORD *)(v4 + 4LL * ++count) = k;
        --*outa;
      }
    }
  }
}