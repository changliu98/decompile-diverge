int __cdecl filenvercmp(const char *a, ptrdiff_t alen, const char *b, ptrdiff_t blen)
{
  bool v6; // [rsp+7h] [rbp-69h]
  _BOOL4 v7; // [rsp+8h] [rbp-68h]
  bool v8; // [rsp+Fh] [rbp-61h]
  _BOOL4 v9; // [rsp+10h] [rbp-60h]
  bool v10; // [rsp+17h] [rbp-59h]
  _BOOL4 v11; // [rsp+18h] [rbp-58h]
  _BOOL4 v12; // [rsp+1Ch] [rbp-54h]
  _BOOL4 v13; // [rsp+20h] [rbp-50h]
  _BOOL4 v14; // [rsp+24h] [rbp-4Ch]
  int result; // [rsp+28h] [rbp-48h]
  idx_t bprefixlen; // [rsp+30h] [rbp-40h]
  idx_t aprefixlen; // [rsp+38h] [rbp-38h]
  ptrdiff_t blena; // [rsp+48h] [rbp-28h] BYREF
  const char *ba; // [rsp+50h] [rbp-20h]
  ptrdiff_t alena; // [rsp+58h] [rbp-18h] BYREF
  const char *aa; // [rsp+60h] [rbp-10h]

  aa = a;
  alena = alen;
  ba = b;
  blena = blen;
  if ( alen >= 0 )
    v14 = alena == 0;
  else
    v14 = *aa == 0;
  if ( blena >= 0 )
    v13 = blena == 0;
  else
    v13 = *ba == 0;
  if ( v14 )
    return -!v13;
  if ( v13 )
    return 1;
  if ( *aa == 46 )
  {
    if ( *ba != 46 )
      return -1;
    if ( alena >= 0 )
      v12 = alena == 1;
    else
      v12 = aa[1] == 0;
    if ( blena >= 0 )
      v11 = blena == 1;
    else
      v11 = ba[1] == 0;
    if ( v12 )
      return -!v11;
    if ( v11 )
      return 1;
    v10 = 0;
    if ( aa[1] == 46 )
    {
      if ( alena >= 0 )
        v9 = alena == 2;
      else
        v9 = aa[2] == 0;
      v10 = v9;
    }
    v8 = 0;
    if ( ba[1] == 46 )
    {
      if ( blena >= 0 )
        v7 = blena == 2;
      else
        v7 = ba[2] == 0;
      v8 = v7;
    }
    if ( v10 )
      return -!v8;
    if ( v8 )
      return 1;
  }
  else if ( *ba == 46 )
  {
    return 1;
  }
  aprefixlen = file_prefixlen(aa, &alena);
  bprefixlen = file_prefixlen(ba, &blena);
  v6 = 0;
  if ( aprefixlen == alena )
    v6 = bprefixlen == blena;
  result = verrevcmp(aa, aprefixlen, ba, bprefixlen);
  if ( result || v6 )
    return result;
  else
    return verrevcmp(aa, alena, ba, blena);
}