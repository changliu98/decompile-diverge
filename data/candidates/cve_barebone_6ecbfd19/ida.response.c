u_int __cdecl ieee802_11_print(
        netdissect_options *ndo,
        const u_char *p,
        u_int length,
        u_int orig_caplen,
        int pad,
        u_int fcslen)
{
  int v7; // [rsp+0h] [rbp-60h]
  int llc_hdrlen; // [rsp+4h] [rbp-5Ch]
  lladdr_info dst; // [rsp+8h] [rbp-58h] BYREF
  lladdr_info src; // [rsp+18h] [rbp-48h] BYREF
  u_int meshdrlen; // [rsp+28h] [rbp-38h]
  u_int hdrlen; // [rsp+2Ch] [rbp-34h]
  u_int caplen; // [rsp+30h] [rbp-30h]
  uint16_t fc; // [rsp+36h] [rbp-2Ah]
  u_int fcslena; // [rsp+38h] [rbp-28h]
  int pada; // [rsp+3Ch] [rbp-24h]
  u_int orig_caplena; // [rsp+40h] [rbp-20h]
  u_int lengtha; // [rsp+44h] [rbp-1Ch]
  const u_char *pa; // [rsp+48h] [rbp-18h]
  netdissect_options *ndoa; // [rsp+50h] [rbp-10h]

  ndoa = ndo;
  pa = p;
  lengtha = length;
  orig_caplena = orig_caplen;
  pada = pad;
  fcslena = fcslen;
  caplen = orig_caplen;
  if ( length >= fcslen )
  {
    lengtha -= fcslena;
    if ( caplen > lengtha )
    {
      fcslena = caplen - lengtha;
      caplen = lengtha;
      ndoa->ndo_snapend -= fcslena;
    }
    if ( caplen < 2 )
    {
      ndoa->ndo_printf(ndoa, "%s", "[|802.11]");
      return orig_caplena;
    }
    fc = *(_WORD *)pa;
    hdrlen = extract_header_length(ndoa, fc);
    if ( !hdrlen )
      return 0;
    if ( pada )
      hdrlen = (hdrlen + 3) & 0xFFFFFFFC;
    if ( ndoa->ndo_Hflag && (((int)fc >> 2) & 3) == 2 && (((int)fc >> 4) & 8) != 0 )
    {
      meshdrlen = extract_mesh_header_length(&pa[hdrlen]);
      hdrlen += meshdrlen;
    }
    else
    {
      meshdrlen = 0;
    }
    if ( caplen < hdrlen )
    {
LABEL_33:
      ndoa->ndo_printf(ndoa, "%s", "[|802.11]");
      return hdrlen;
    }
    if ( ndoa->ndo_eflag )
      ieee_802_11_hdr_print(ndoa, fc, pa, hdrlen, meshdrlen);
    lengtha -= hdrlen;
    caplen -= hdrlen;
    pa += hdrlen;
    src.addr_string = (const char *(*)(netdissect_options *, const u_char *))etheraddr_string;
    dst.addr_string = (const char *(*)(netdissect_options *, const u_char *))etheraddr_string;
    v7 = (fc >> 2) & 3;
    if ( v7 )
    {
      if ( v7 == 1 )
      {
        if ( !ctrl_body_print(ndoa, fc, &pa[-hdrlen]) )
          goto LABEL_33;
      }
      else if ( v7 == 2 )
      {
        if ( (((int)fc >> 4) & 4) != 0 )
          return hdrlen;
        if ( (fc & 0x4000) != 0 )
        {
          ndoa->ndo_printf(ndoa, "Data");
          if ( !wep_print(ndoa, pa) )
            goto LABEL_33;
        }
        else
        {
          get_data_src_dst_mac(fc, &pa[-hdrlen], &src.addr, &dst.addr);
          llc_hdrlen = llc_print(ndoa, pa, lengtha, caplen, &src, &dst);
          if ( llc_hdrlen < 0 )
          {
            if ( !ndoa->ndo_suppress_default_print )
              ndoa->ndo_default_print(ndoa, pa, caplen);
            llc_hdrlen = -llc_hdrlen;
          }
          hdrlen += llc_hdrlen;
        }
      }
    }
    else
    {
      get_mgmt_src_dst_mac(&pa[-hdrlen], &src.addr, &dst.addr);
      if ( !mgmt_body_print(ndoa, fc, src.addr, pa, lengtha) )
      {
        ndoa->ndo_printf(ndoa, "%s", "[|802.11]");
        return hdrlen;
      }
    }
    return hdrlen;
  }
  ndoa->ndo_printf(ndoa, "%s", "[|802.11]");
  return caplen;
}