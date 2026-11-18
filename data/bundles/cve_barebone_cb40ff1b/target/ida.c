int __cdecl isis_print_mt_capability_subtlv(netdissect_options *ndo, const uint8_t *tptr, int len)
{
  const uint8_t *v3; // rax
  const char *v4; // rax
  const uint8_t *v5; // rax
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+8h] [rbp-38h]
  int tmp; // [rsp+18h] [rbp-28h]
  unsigned int stlv_len; // [rsp+1Ch] [rbp-24h]
  int stlv_lena; // [rsp+1Ch] [rbp-24h]
  unsigned int stlv_type; // [rsp+20h] [rbp-20h]
  const uint8_t *tptrb; // [rsp+28h] [rbp-18h]
  const uint8_t *tptrc; // [rsp+28h] [rbp-18h]
  const uint8_t *tptrd; // [rsp+28h] [rbp-18h]

  while ( 1 )
  {
    while ( 1 )
    {
      if ( len <= 2 )
        return 0;
      stlv_type = *tptr;
      v3 = tptr + 1;
      tptr += 2;
      stlv_len = *v3;
      ndo_printf = ndo->ndo_printf;
      v4 = tok2str(&isis_mt_capability_subtlv_values, "unknown", stlv_type);
      ndo_printf(ndo, "\n\t      %s subTLV #%u, length: %u", v4, stlv_type, stlv_len);
      len -= 2;
      if ( stlv_type == 1 )
        break;
      if ( stlv_type == 3 )
      {
        if ( ndo->ndo_snapend - 8 > ndo->ndo_snapend || tptr > ndo->ndo_snapend - 8 )
          goto trunc;
        ndo->ndo_printf(ndo, (const char *)&unk_210D, _byteswap_ulong(*(_DWORD *)tptr));
        tptrd = tptr + 4;
        ndo->ndo_printf(ndo, "%04x", _byteswap_ushort(*(_WORD *)tptrd));
        tptrd += 2;
        ndo->ndo_printf(
          ndo,
          ", RES: %d, VID: %d",
          (int)_byteswap_ushort(*(_WORD *)tptrd) >> 12,
          _byteswap_ushort(*(_WORD *)tptrd) & 0xFFF);
        tptr = tptrd + 2;
        len -= 8;
        for ( stlv_lena = stlv_len - 8; stlv_lena >= 4; stlv_lena -= 4 )
        {
          if ( ndo->ndo_snapend - 4 > ndo->ndo_snapend || tptr > ndo->ndo_snapend - 4 )
            goto trunc;
          ndo->ndo_printf(
            ndo,
            "\n\t        T: %d, R: %d, RES: %d, ISID: %d",
            _byteswap_ulong(*(_DWORD *)tptr) >> 31,
            (_byteswap_ulong(*(_DWORD *)tptr) >> 30) & 1,
            (_byteswap_ulong(*(_DWORD *)tptr) >> 24) & 0x3F,
            _byteswap_ulong(*(_DWORD *)tptr) & 0xFFFFFF);
          tptr += 4;
          len -= 4;
        }
      }
    }
    if ( ndo->ndo_snapend - 19 > ndo->ndo_snapend || tptr > ndo->ndo_snapend - 19 )
      break;
    ndo->ndo_printf(ndo, "\n\t        CIST Root-ID: %08x", _byteswap_ulong(*(_DWORD *)tptr));
    tptrb = tptr + 4;
    ndo->ndo_printf(ndo, " %08x", _byteswap_ulong(*(_DWORD *)tptrb));
    tptrb += 4;
    ndo->ndo_printf(ndo, ", Path Cost: %08x", _byteswap_ulong(*(_DWORD *)tptrb));
    tptrb += 4;
    ndo->ndo_printf(ndo, ", Prio: %d", _byteswap_ushort(*(_WORD *)tptrb));
    tptrb += 2;
    ndo->ndo_printf(ndo, "\n\t        RES: %d", (int)_byteswap_ushort(*(_WORD *)tptrb) >> 5);
    ndo->ndo_printf(ndo, ", V: %d", ((int)_byteswap_ushort(*(_WORD *)tptrb) >> 4) & 1);
    ndo->ndo_printf(ndo, ", SPSource-ID: %d", _byteswap_ulong(*(_DWORD *)tptrb) & 0xFFFFF);
    tptrb += 4;
    ndo->ndo_printf(ndo, ", No of Trees: %x", *tptrb);
    v5 = tptrb;
    tptr = tptrb + 1;
    tmp = *v5;
    len -= 19;
    while ( tmp )
    {
      if ( ndo->ndo_snapend - 8 > ndo->ndo_snapend || tptr > ndo->ndo_snapend - 8 )
        goto trunc;
      ndo->ndo_printf(
        ndo,
        "\n\t         U:%d, M:%d, A:%d, RES:%d",
        (int)*tptr >> 7,
        ((int)*tptr >> 6) & 1,
        ((int)*tptr >> 5) & 1,
        *tptr & 0x1F);
      tptrc = tptr + 1;
      ndo->ndo_printf(ndo, ", ECT: %08x", _byteswap_ulong(*(_DWORD *)tptrc));
      tptrc += 4;
      ndo->ndo_printf(
        ndo,
        ", BVID: %d, SPVID: %d",
        ((unsigned int)(tptrc[2] | (tptrc[1] << 8) | (*tptrc << 16)) >> 12) & 0xFFF,
        _byteswap_ushort(*(_WORD *)(tptrc + 1)) & 0xFFF);
      tptr = tptrc + 3;
      len -= 8;
      --tmp;
    }
  }
trunc:
  ndo->ndo_printf(ndo, "\n\t\t");
  ndo->ndo_printf(ndo, "%s", " [|isis]");
  return 1;
}