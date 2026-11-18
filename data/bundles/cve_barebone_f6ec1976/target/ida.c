void __cdecl bgp_capabilities_print(netdissect_options *ndo, const u_char *opt, int caps_len)
{
  const char *v3; // rax
  const char *v4; // r8
  const char *v5; // rdx
  const char *v6; // r8
  const char *v7; // rax
  char *v8; // rax
  const char *v9; // rax
  const char *v10; // [rsp+18h] [rbp-B8h]
  unsigned int v11; // [rsp+24h] [rbp-ACh]
  const char *v12; // [rsp+28h] [rbp-A8h]
  unsigned int v13; // [rsp+34h] [rbp-9Ch]
  int (*v14)(netdissect_options *, const char *, ...); // [rsp+38h] [rbp-98h]
  int (*v15)(netdissect_options *, const char *, ...); // [rsp+48h] [rbp-88h]
  const char *v16; // [rsp+58h] [rbp-78h]
  unsigned int v17; // [rsp+64h] [rbp-6Ch]
  int (*v18)(netdissect_options *, const char *, ...); // [rsp+68h] [rbp-68h]
  const char *v19; // [rsp+78h] [rbp-58h]
  unsigned int v20; // [rsp+84h] [rbp-4Ch]
  int (*v21)(netdissect_options *, const char *, ...); // [rsp+88h] [rbp-48h]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+A0h] [rbp-30h]
  int i; // [rsp+A8h] [rbp-28h]
  int cap_offset; // [rsp+ACh] [rbp-24h]
  int cap_offseta; // [rsp+ACh] [rbp-24h]
  int tcap_len; // [rsp+B0h] [rbp-20h]
  int tcap_lena; // [rsp+B0h] [rbp-20h]
  int cap_len; // [rsp+B4h] [rbp-1Ch]
  unsigned int cap_type; // [rsp+B8h] [rbp-18h]

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
trunc:
      ndo->ndo_printf(ndo, "[|BGP]");
      return;
    }
    if ( cap_type == 1 )
    {
      v21 = ndo->ndo_printf;
      v19 = tok2str(&af_values, "Unknown", _byteswap_ushort(*(_WORD *)&opt[i + 2]));
      v20 = _byteswap_ushort(*(_WORD *)&opt[i + 2]);
      v4 = tok2str(&bgp_safi_values, "Unknown", opt[i + 5]);
      v21(ndo, "\n\t\tAFI %s (%u), SAFI %s (%u)", v19, v20, v4, opt[i + 5]);
    }
    else if ( cap_type != 2 )
    {
      switch ( cap_type )
      {
        case '@':
          if ( ndo->ndo_snapend - 2 > ndo->ndo_snapend || &opt[i + 2] > ndo->ndo_snapend - 2 )
            goto trunc;
          v5 = "none";
          if ( (opt[i + 2] & 0x80) != 0 )
            v5 = "R";
          ndo->ndo_printf(
            ndo,
            "\n\t\tRestart Flags: [%s], Restart Time %us",
            v5,
            _byteswap_ushort(*(_WORD *)&opt[i + 2]) & 0xFFF);
          tcap_lena = cap_len - 2;
          cap_offset = 4;
          while ( tcap_lena >= 4 )
          {
            v18 = ndo->ndo_printf;
            v16 = tok2str(&af_values, "Unknown", _byteswap_ushort(*(_WORD *)&opt[i + cap_offset]));
            v17 = _byteswap_ushort(*(_WORD *)&opt[i + cap_offset]);
            v6 = tok2str(&bgp_safi_values, "Unknown", opt[cap_offset + 2 + i]);
            v7 = "no";
            if ( (opt[cap_offset + 3 + i] & 0x80) != 0 )
              v7 = "yes";
            v18(
              ndo,
              "\n\t\t  AFI %s (%u), SAFI %s (%u), Forwarding state preserved: %s",
              v16,
              v17,
              v6,
              opt[cap_offset + 2 + i],
              v7);
            tcap_lena -= 4;
            cap_offset += 4;
          }
          break;
        case 'A':
          if ( cap_len == 4 )
          {
            v15 = ndo->ndo_printf;
            v8 = as_printf(ndo, astostr, 20, _byteswap_ulong(*(_DWORD *)&opt[i + 2]));
            v15(ndo, "\n\t\t 4 Byte AS %s", v8);
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
                goto LABEL_41;
              }
              v14 = ndo->ndo_printf;
              v10 = tok2str(&af_values, "Unknown", _byteswap_ushort(*(_WORD *)&opt[i + cap_offseta]));
              v11 = _byteswap_ushort(*(_WORD *)&opt[i + cap_offseta]);
              v12 = tok2str(&bgp_safi_values, "Unknown", opt[cap_offseta + 2 + i]);
              v13 = opt[cap_offseta + 2 + i];
              v9 = tok2str(&bgp_add_path_recvsend, "Bogus (0x%02x)", opt[cap_offseta + 3 + i]);
              v14(ndo, "\n\t\tAFI %s (%u), SAFI %s (%u), Send/Receive: %s", v10, v11, v12, v13, v9);
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
LABEL_41:
    if ( ndo->ndo_vflag > 1 && cap_len > 0 )
      print_unknown_data(ndo, &opt[i + 2], "\n\t\t", cap_len);
  }
}