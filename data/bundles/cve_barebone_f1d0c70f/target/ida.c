void __cdecl ip_optprint(netdissect_options *ndo, const u_char *cp, u_int length)
{
  const char *v3; // rax
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+10h] [rbp-30h]
  u_int option_code; // [rsp+1Ch] [rbp-24h]
  const char *sep; // [rsp+20h] [rbp-20h]
  u_int option_len; // [rsp+28h] [rbp-18h]

  sep = "";
  while ( length )
  {
    ndo->ndo_printf(ndo, "%s", sep);
    sep = ",";
    if ( ndo->ndo_snapend - 1 > ndo->ndo_snapend || cp > ndo->ndo_snapend - 1 )
      goto trunc;
    option_code = *cp;
    ndo_printf = ndo->ndo_printf;
    v3 = tok2str(&ip_option_values, "unknown %u", option_code);
    ndo_printf(ndo, "%s", v3);
    if ( option_code > 1 )
    {
      if ( ndo->ndo_snapend - 1 > ndo->ndo_snapend || cp + 1 > ndo->ndo_snapend - 1 )
        goto trunc;
      option_len = cp[1];
      if ( option_len < 2 )
        goto LABEL_12;
    }
    else
    {
      option_len = 1;
    }
    if ( option_len > length )
    {
LABEL_12:
      ndo->ndo_printf(ndo, " [bad length %u]", option_len);
      return;
    }
    if ( &ndo->ndo_snapend[-(unsigned __int64)option_len] > ndo->ndo_snapend
      || cp > &ndo->ndo_snapend[-(unsigned __int64)option_len] )
    {
trunc:
      ndo->ndo_printf(ndo, "%s", "[|ip]");
      return;
    }
    if ( !option_code )
      return;
    if ( option_code != 1 )
    {
      switch ( option_code )
      {
        case 7u:
          goto LABEL_28;
        case 0x44u:
          ip_printts(ndo, cp, option_len);
          break;
        case 0x82u:
          break;
        case 0x83u:
        case 0x89u:
LABEL_28:
          ip_printroute(ndo, cp, option_len);
          break;
        case 0x94u:
          if ( option_len >= 4 )
          {
            if ( ndo->ndo_snapend - 1 > ndo->ndo_snapend || cp + 3 > ndo->ndo_snapend - 1 )
              goto trunc;
            if ( _byteswap_ushort(*((_WORD *)cp + 1)) )
              ndo->ndo_printf(ndo, " value %u", _byteswap_ushort(*((_WORD *)cp + 1)));
          }
          else
          {
            ndo->ndo_printf(ndo, " [bad length %u]", option_len);
          }
          break;
      }
    }
    cp += option_len;
    length -= option_len;
  }
}