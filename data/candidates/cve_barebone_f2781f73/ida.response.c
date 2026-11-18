void __cdecl bgp_capabilities_print(netdissect_options *ndo, const u_char *opt, int caps_len)
{
  const char *v3; // rax
  uint16_t v4; // ax
  const char *v5; // r8
  const char *v6; // rax
  uint16_t v7; // ax
  uint16_t v8; // ax
  const char *v9; // r8
  const char *v10; // rax
  u_int v11; // eax
  char *v12; // rax
  uint16_t v13; // ax
  const char *v14; // rax
  const char *v15; // [rsp+18h] [rbp-D8h]
  unsigned int v16; // [rsp+24h] [rbp-CCh]
  const char *v17; // [rsp+28h] [rbp-C8h]
  unsigned int v18; // [rsp+34h] [rbp-BCh]
  int (*v19)(netdissect_options *, const char *, ...); // [rsp+38h] [rbp-B8h]
  int (*v20)(netdissect_options *, const char *, ...); // [rsp+50h] [rbp-A0h]
  const char *v21; // [rsp+60h] [rbp-90h]
  unsigned int v22; // [rsp+6Ch] [rbp-84h]
  int (*v23)(netdissect_options *, const char *, ...); // [rsp+70h] [rbp-80h]
  const char *v24; // [rsp+80h] [rbp-70h]
  int (*v25)(netdissect_options *, const char *, ...); // [rsp+88h] [rbp-68h]
  const char *v26; // [rsp+98h] [rbp-58h]
  unsigned int v27; // [rsp+A4h] [rbp-4Ch]
  int (*v28)(netdissect_options *, const char *, ...); // [rsp+A8h] [rbp-48h]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+C0h] [rbp-30h]
  int i; // [rsp+C8h] [rbp-28h]
  int cap_offset; // [rsp+CCh] [rbp-24h]
  int cap_offseta; // [rsp+CCh] [rbp-24h]
  int tcap_len; // [rsp+D0h] [rbp-20h]
  int tcap_lena; // [rsp+D0h] [rbp-20h]
  int cap_len; // [rsp+D4h] [rbp-1Ch]
  unsigned int cap_type; // [rsp+D8h] [rbp-18h]

  for ( i = 0; i < caps_len; i += cap_len + 2 )
  {
    if ( ndo->ndo_snapend - 2 > ndo->ndo_snapend
      || &opt[i] > ndo->ndo_snapend - 2
      || (cap_type = opt[i],
          cap_len = opt[i + 1],
          tcap_len = cap_len,
          ndo_printf = ndo->ndo_printf,
          v3 = tok2str(&bgp_capcode_values, "Unknown", cap_type),
          ndo_printf(ndo, "\n\t      %s (%u), length: %u", v3, cap_type, (unsigned int)cap_len),
          &ndo->ndo_snapend[-cap_len] > ndo->ndo_snapend)
      || &opt[i + 2] > &ndo->ndo_snapend[-cap_len] )
    {
      ndo->ndo_printf(ndo, "[|BGP]");
      return;
    }
    if ( cap_type == 1 )
    {
      v28 = ndo->ndo_printf;
      v4 = EXTRACT_16BITS(&opt[i + 2]);
      v26 = tok2str(&af_values, "Unknown", v4);
      v27 = EXTRACT_16BITS(&opt[i + 2]);
      v5 = tok2str(&bgp_safi_values, "Unknown", opt[i + 5]);
      v28(ndo, "\n\t\tAFI %s (%u), SAFI %s (%u)", v26, v27, v5, opt[i + 5]);
    }
    else if ( cap_type != 2 )
    {
      switch ( cap_type )
      {
        case '@':
          v25 = ndo->ndo_printf;
          v6 = "none";
          if ( (opt[i + 2] & 0x80) != 0 )
            v6 = "R";
          v24 = v6;
          v7 = EXTRACT_16BITS(&opt[i + 2]);
          v25(ndo, "\n\t\tRestart Flags: [%s], Restart Time %us", v24, v7 & 0xFFF);
          tcap_lena = cap_len - 2;
          cap_offset = 4;
          while ( tcap_lena >= 4 )
          {
            v23 = ndo->ndo_printf;
            v8 = EXTRACT_16BITS(&opt[i + cap_offset]);
            v21 = tok2str(&af_values, "Unknown", v8);
            v22 = EXTRACT_16BITS(&opt[i + cap_offset]);
            v9 = tok2str(&bgp_safi_values, "Unknown", opt[cap_offset + 2 + i]);
            v10 = "no";
            if ( (opt[cap_offset + 3 + i] & 0x80) != 0 )
              v10 = "yes";
            v23(
              ndo,
              "\n\t\t  AFI %s (%u), SAFI %s (%u), Forwarding state preserved: %s",
              v21,
              v22,
              v9,
              opt[cap_offset + 2 + i],
              v10);
            tcap_lena -= 4;
            cap_offset += 4;
          }
          break;
        case 'A':
          if ( cap_len == 4 )
          {
            v20 = ndo->ndo_printf;
            v11 = EXTRACT_32BITS(&opt[i + 2]);
            v12 = as_printf(ndo, astostr, 20, v11);
            v20(ndo, "\n\t\t 4 Byte AS %s", v12);
          }
          break;
        case 'E':
          cap_offseta = 2;
          if ( cap_len )
          {
            while ( tcap_len > 0 )
            {
              if ( tcap_len < 4 )
              {
                ndo->ndo_printf(ndo, "\n\t\t(invalid)");
                goto LABEL_38;
              }
              v19 = ndo->ndo_printf;
              v13 = EXTRACT_16BITS(&opt[i + cap_offseta]);
              v15 = tok2str(&af_values, "Unknown", v13);
              v16 = EXTRACT_16BITS(&opt[i + cap_offseta]);
              v17 = tok2str(&bgp_safi_values, "Unknown", opt[cap_offseta + 2 + i]);
              v18 = opt[cap_offseta + 2 + i];
              v14 = tok2str(&bgp_add_path_recvsend, "Bogus (0x%02x)", opt[cap_offseta + 3 + i]);
              v19(ndo, "\n\t\tAFI %s (%u), SAFI %s (%u), Send/Receive: %s", v15, v16, v17, v18, v14);
              tcap_len -= 4;
              cap_offseta += 4;
            }
          }
          else
          {
            ndo->ndo_printf(ndo, " (bogus)");
          }
          break;
        default:
          if ( cap_type != 128 )
          {
            ndo->ndo_printf(ndo, "\n\t\tno decoder for Capability %u", cap_type);
            if ( ndo->ndo_vflag <= 1 )
              print_unknown_data(ndo, &opt[i + 2], "\n\t\t", cap_len);
          }
          break;
      }
    }
LABEL_38:
    if ( ndo->ndo_vflag > 1 && cap_len > 0 )
      print_unknown_data(ndo, &opt[i + 2], "\n\t\t", cap_len);
  }
}