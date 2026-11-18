void __cdecl jpc_qmfb_split_colgrp(jpc_fix_t *a, int numrows, int stride, int parity)
{
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int hstartcol; // [rsp+8h] [rbp-80058h]
  int m; // [rsp+Ch] [rbp-80054h]
  int i; // [rsp+10h] [rbp-80050h]
  int ia; // [rsp+10h] [rbp-80050h]
  int ib; // [rsp+10h] [rbp-80050h]
  int n; // [rsp+14h] [rbp-8004Ch]
  int na; // [rsp+14h] [rbp-8004Ch]
  int nb; // [rsp+14h] [rbp-8004Ch]
  jpc_fix_t *dstptr2; // [rsp+18h] [rbp-80048h]
  jpc_fix_t *dstptr2a; // [rsp+18h] [rbp-80048h]
  jpc_fix_t *dstptr2b; // [rsp+18h] [rbp-80048h]
  jpc_fix_t *srcptr2; // [rsp+20h] [rbp-80040h]
  jpc_fix_t *srcptr2a; // [rsp+20h] [rbp-80040h]
  jpc_fix_t *srcptr2b; // [rsp+20h] [rbp-80040h]
  jpc_fix_t *dstptr; // [rsp+28h] [rbp-80038h]
  jpc_fix_t *dstptra; // [rsp+28h] [rbp-80038h]
  jpc_fix_t *dstptrb; // [rsp+28h] [rbp-80038h]
  jpc_fix_t *srcptr; // [rsp+30h] [rbp-80030h]
  jpc_fix_t *srcptra; // [rsp+30h] [rbp-80030h]
  jpc_fix_t *srcptrb; // [rsp+30h] [rbp-80030h]
  jpc_fix_t *buf; // [rsp+38h] [rbp-80028h]
  jpc_fix_t splitbuf[65536]; // [rsp+40h] [rbp-80020h] BYREF
  int bufsize; // [rsp+80048h] [rbp-18h]
  int paritya; // [rsp+8004Ch] [rbp-14h]
  int stridea; // [rsp+80050h] [rbp-10h]
  int numrowsa; // [rsp+80054h] [rbp-Ch]
  jpc_fix_t *aa; // [rsp+80058h] [rbp-8h]

  aa = a;
  numrowsa = numrows;
  stridea = stride;
  paritya = parity;
  bufsize = (numrows + 1) >> 1;
  buf = splitbuf;
  if ( bufsize > 4096 )
  {
    buf = (jpc_fix_t *)jas_alloc2(bufsize, 8uLL);
    if ( !buf )
      abort();
  }
  if ( numrowsa >= 2 )
  {
    hstartcol = (numrowsa + 1 - paritya) >> 1;
    m = numrowsa - hstartcol;
    n = numrowsa - hstartcol;
    dstptr = buf;
    for ( srcptr = &aa[stridea * (1 - paritya)]; ; srcptr += 2 * stridea )
    {
      v4 = n--;
      if ( v4 <= 0 )
        break;
      dstptr2 = dstptr;
      srcptr2 = srcptr;
      for ( i = 0; i < 16; ++i )
        *dstptr2++ = *srcptr2++;
      dstptr += 16;
    }
    dstptra = &aa[stridea * (1 - paritya)];
    srcptra = &aa[stridea * (2 - paritya)];
    na = (__PAIR64__(numrowsa - m, paritya) - 1) >> 32;
    while ( 1 )
    {
      v5 = na--;
      if ( v5 <= 0 )
        break;
      dstptr2a = dstptra;
      srcptr2a = srcptra;
      for ( ia = 0; ia < 16; ++ia )
        *dstptr2a++ = *srcptr2a++;
      dstptra += stridea;
      srcptra += 2 * stridea;
    }
    dstptrb = &aa[stridea * hstartcol];
    srcptrb = buf;
    nb = m;
    while ( 1 )
    {
      v6 = nb--;
      if ( v6 <= 0 )
        break;
      dstptr2b = dstptrb;
      srcptr2b = srcptrb;
      for ( ib = 0; ib < 16; ++ib )
        *dstptr2b++ = *srcptr2b++;
      dstptrb += stridea;
      srcptrb += 16;
    }
  }
  if ( buf != splitbuf )
    jas_free(buf);
}