void __cdecl vrrp_print(netdissect_options *ndo, const u_char *bp_0, u_int len, const u_char *bp2, int ttl)
{
  const char *v5; // rax
  uint16_t v6; // ax
  uint16_t v7; // ax
  const char *v8; // rax
  netdissect_options *v9; // [rsp+0h] [rbp-B0h]
  unsigned int v10; // [rsp+Ch] [rbp-A4h]
  int (*v11)(netdissect_options *, const char *, ...); // [rsp+10h] [rbp-A0h]
  netdissect_options *v12; // [rsp+18h] [rbp-98h]
  int (*v13)(netdissect_options *, const char *, ...); // [rsp+20h] [rbp-90h]
  netdissect_options *v14; // [rsp+28h] [rbp-88h]
  int (*v15)(netdissect_options *, const char *, ...); // [rsp+30h] [rbp-80h]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+40h] [rbp-70h]
  cksum_vec vec[1]; // [rsp+50h] [rbp-60h] BYREF
  char c; // [rsp+6Bh] [rbp-45h]
  int i; // [rsp+6Ch] [rbp-44h]
  int naddrs; // [rsp+70h] [rbp-40h]
  uint16_t intvl; // [rsp+76h] [rbp-3Ah]
  const char *type_s; // [rsp+78h] [rbp-38h]
  int auth_type; // [rsp+80h] [rbp-30h]
  int type; // [rsp+84h] [rbp-2Ch]
  int version; // [rsp+88h] [rbp-28h]
  int ttla; // [rsp+8Ch] [rbp-24h]
  const u_char *bp2a; // [rsp+90h] [rbp-20h]
  u_int lena; // [rsp+9Ch] [rbp-14h]
  const u_char *bp_0a; // [rsp+A0h] [rbp-10h]
  netdissect_options *ndoa; // [rsp+A8h] [rbp-8h]

  ndoa = ndo;
  bp_0a = bp_0;
  lena = len;
  bp2a = bp2;
  ttla = ttl;
  auth_type = 0;
  if ( ndo->ndo_snapend - 1 > ndo->ndo_snapend || bp_0a > ndoa->ndo_snapend - 1 )
    goto trunc;
  version = (*bp_0a & 0xF0) >> 4;
  type = *bp_0a & 0xF;
  type_s = tok2str(&type2str, "unknown type (%u)", type);
  ndoa->ndo_printf(ndoa, "VRRPv%u, %s", (unsigned int)version, type_s);
  if ( ttla != 255 )
    ndoa->ndo_printf(ndoa, ", (ttl %u)", (unsigned int)ttla);
  if ( version >= 2 && version <= 3 && type == 1 )
  {
    if ( ndoa->ndo_snapend - 1 > ndoa->ndo_snapend )
      goto trunc;
    if ( bp_0a + 2 > ndoa->ndo_snapend - 1 )
      goto trunc;
    ndoa->ndo_printf(ndoa, ", vrid %u, prio %u", bp_0a[1], bp_0a[2]);
    if ( ndoa->ndo_snapend - 1 > ndoa->ndo_snapend || bp_0a + 5 > ndoa->ndo_snapend - 1 )
      goto trunc;
    if ( version == 2 )
    {
      auth_type = bp_0a[4];
      ndo_printf = ndoa->ndo_printf;
      v5 = tok2str(&auth2str, 0LL, auth_type);
      ndo_printf(ndoa, ", authtype %s", v5);
      ndoa->ndo_printf(ndoa, ", intvl %us, length %u", bp_0a[5], lena);
    }
    else
    {
      intvl = bp_0a[5] | ((bp_0a[4] & 0xF) << 8);
      ndoa->ndo_printf(ndoa, ", intvl %ucs, length %u", intvl, lena);
    }
    if ( !ndoa->ndo_vflag )
      return;
    naddrs = bp_0a[3];
    if ( version == 2
      && &ndoa->ndo_snapend[-(unsigned __int64)lena] <= ndoa->ndo_snapend
      && bp_0a <= &ndoa->ndo_snapend[-(unsigned __int64)lena] )
    {
      vec[0].ptr = bp_0a;
      vec[0].len = lena;
      if ( in_cksum(vec, 1) )
      {
        if ( ndoa->ndo_snapend - 2 > ndoa->ndo_snapend || bp_0a + 6 > ndoa->ndo_snapend - 2 )
          goto trunc;
        v15 = ndoa->ndo_printf;
        v14 = ndoa;
        v6 = EXTRACT_16BITS(bp_0a + 6);
        v15(v14, ", (bad vrrp cksum %x)", v6);
      }
    }
    if ( version == 3
      && &ndoa->ndo_snapend[-(unsigned __int64)lena] <= ndoa->ndo_snapend
      && bp_0a <= &ndoa->ndo_snapend[-(unsigned __int64)lena]
      && (unsigned __int16)nextproto4_cksum(ndoa, (const ip *)bp2a, bp_0a, lena, lena, 0x70u) )
    {
      v13 = ndoa->ndo_printf;
      v12 = ndoa;
      v7 = EXTRACT_16BITS(bp_0a + 6);
      v13(v12, ", (bad vrrp cksum %x)", v7);
    }
    ndoa->ndo_printf(ndoa, ", addrs");
    if ( naddrs > 1 )
      ndoa->ndo_printf(ndoa, "(%d)", (unsigned int)naddrs);
    ndoa->ndo_printf(ndoa, ":");
    c = 32;
    bp_0a += 8;
    for ( i = 0; i < naddrs; ++i )
    {
      if ( ndoa->ndo_snapend - 1 > ndoa->ndo_snapend || bp_0a + 3 > ndoa->ndo_snapend - 1 )
        goto trunc;
      v11 = ndoa->ndo_printf;
      v9 = ndoa;
      v10 = c;
      v8 = getname(ndoa, bp_0a);
      v11(v9, "%c%s", v10, v8);
      c = 44;
      bp_0a += 4;
    }
    if ( version != 2 || auth_type != 1 )
      return;
    if ( ndoa->ndo_snapend - 1 <= ndoa->ndo_snapend && bp_0a + 7 <= ndoa->ndo_snapend - 1 )
    {
      ndoa->ndo_printf(ndoa, " auth \"");
      if ( !fn_printn(ndoa, bp_0a, 8u, ndoa->ndo_snapend) )
      {
        ndoa->ndo_printf(ndoa, "\"");
        return;
      }
      ndoa->ndo_printf(ndoa, "\"");
    }
trunc:
    ndoa->ndo_printf(ndoa, "[|vrrp]");
  }
}