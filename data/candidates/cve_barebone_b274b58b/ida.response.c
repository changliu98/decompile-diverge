u_int __cdecl mfr_print(netdissect_options *ndo, const u_char *p, u_int length)
{
  const char *v3; // rax
  const char *v4; // rax
  uint32_t v5; // eax
  char *v6; // rax
  char *v7; // rax
  int (*v9)(netdissect_options *, const char *, ...); // [rsp+10h] [rbp-A0h]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+28h] [rbp-88h]
  bool v11; // [rsp+37h] [rbp-79h]
  int (*v12)(netdissect_options *, const char *, ...); // [rsp+40h] [rbp-70h]
  int (*v13)(netdissect_options *, const char *, ...); // [rsp+58h] [rbp-58h]
  char *v14; // [rsp+68h] [rbp-48h]
  int (*v15)(netdissect_options *, const char *, ...); // [rsp+70h] [rbp-40h]
  const uint8_t *tptr; // [rsp+78h] [rbp-38h]
  const timeval *tptra; // [rsp+78h] [rbp-38h]
  uint8_t ie_len; // [rsp+84h] [rbp-2Ch]
  uint8_t ie_lena; // [rsp+84h] [rbp-2Ch]
  uint8_t ie_type; // [rsp+85h] [rbp-2Bh]
  uint16_t sequence_num; // [rsp+86h] [rbp-2Ah]
  u_int idx; // [rsp+8Ch] [rbp-24h]
  u_int tlen; // [rsp+90h] [rbp-20h]
  u_int tlena; // [rsp+90h] [rbp-20h]

  if ( ndo->ndo_snapend - 4 <= ndo->ndo_snapend && p <= ndo->ndo_snapend - 4 )
  {
    if ( (*p & 0xE0) != 224 || p[1] )
    {
      sequence_num = p[1] | ((*p & 0x1E) << 7);
      if ( (*p & 0xE0) == 192 || (*p & 0xE0) == 128 )
      {
        ndo_printf = ndo->ndo_printf;
        v6 = bittok2str(&frf_flag_values, "none", *p & 0xE0);
        ndo_printf(ndo, "FRF.16 Frag, seq %u, Flags [%s], ", sequence_num, v6);
        fr_print(ndo, p + 2, length - 2);
        return 2;
      }
      else
      {
        v9 = ndo->ndo_printf;
        v7 = bittok2str(&frf_flag_values, "none", *p & 0xE0);
        v9(ndo, "FRF.16 Frag, seq %u, Flags [%s]", sequence_num, v7);
        print_unknown_data(ndo, p, "\n\t", length);
        return 0;
      }
    }
    else
    {
      v15 = ndo->ndo_printf;
      v14 = bittok2str(&frf_flag_values, "none", *p & 0xE0);
      v3 = tok2str(&mfr_ctrl_msg_values, "Unknown Message (0x%02x)", p[2]);
      v15(ndo, "FRF.16 Control, Flags [%s], %s, length %u", v14, v3, length);
      tptr = p + 3;
      tlen = length - 3;
      if ( ndo->ndo_vflag )
      {
        while ( tlen > 2uLL )
        {
          if ( ndo->ndo_snapend - 2 > ndo->ndo_snapend || tptr > ndo->ndo_snapend - 2 )
            goto trunc;
          ie_type = *tptr;
          ie_len = tptr[1];
          v13 = ndo->ndo_printf;
          v4 = tok2str(&mfr_ctrl_ie_values, "Unknown", *tptr);
          v13(ndo, "\n\tIE %s (%u), length %u: ", v4, ie_type, ie_len);
          if ( !ie_type || ie_len <= 2uLL )
            return 3;
          if ( &ndo->ndo_snapend[-(unsigned __int64)ie_len] > ndo->ndo_snapend
            || tptr > &ndo->ndo_snapend[-(unsigned __int64)ie_len] )
          {
            goto trunc;
          }
          tptra = (const timeval *)(tptr + 2);
          ie_lena = ie_len - 2;
          tlena = tlen - 2;
          switch ( ie_type )
          {
            case 1u:
            case 2u:
              for ( idx = 0; ; ++idx )
              {
                v11 = 0;
                if ( idx < ie_lena )
                  v11 = idx < 0x32;
                if ( !v11 || !*((_BYTE *)&tptra->tv_sec + idx) )
                  break;
                safeputchar(ndo, *((_BYTE *)&tptra->tv_sec + idx));
              }
              break;
            case 3u:
              v12 = ndo->ndo_printf;
              v5 = EXTRACT_32BITS(tptra);
              v12(ndo, "0x%08x", v5);
              break;
            case 5u:
              if ( ie_lena != 16LL )
                goto LABEL_30;
              ts_print(ndo, tptra);
              break;
            default:
LABEL_30:
              if ( ndo->ndo_vflag <= 1 )
                print_unknown_data(ndo, (const u_char *)tptra, "\n\t  ", ie_lena);
              break;
          }
          if ( ndo->ndo_vflag > 1 )
            print_unknown_data(ndo, (const u_char *)tptra, "\n\t  ", ie_lena);
          tlen = tlena - ie_lena;
          tptr = (const uint8_t *)tptra + ie_lena;
        }
        return 3;
      }
      else
      {
        return 3;
      }
    }
  }
  else
  {
trunc:
    ndo->ndo_printf(ndo, "[|mfr]");
    return length;
  }
}