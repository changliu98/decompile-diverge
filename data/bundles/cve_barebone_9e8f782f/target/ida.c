void __cdecl isoclns_print(netdissect_options *ndo, const uint8_t *p, u_int length, u_int caplen)
{
  const char *v4; // rdx
  const char *v5; // rdx
  const char *v6; // rdx
  int v7; // [rsp+4h] [rbp-2Ch]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+10h] [rbp-20h]

  if ( caplen > 1 )
  {
    if ( ndo->ndo_eflag )
    {
      ndo_printf = ndo->ndo_printf;
      v4 = tok2str(&nlpid_values, "Unknown", *p);
      ndo_printf(ndo, "OSI NLPID %s (0x%02x): ", v4, *p);
    }
    v7 = *p;
    if ( *p )
    {
      switch ( v7 )
      {
        case 8:
          q933_print(ndo, p + 1, length - 1);
          break;
        case 129:
          if ( !clnp_print(ndo, p, length) )
            print_unknown_data(ndo, p, "\n\t", caplen);
          break;
        case 130:
          esis_print(ndo, p, length);
          break;
        case 131:
          if ( !isis_print(ndo, p, length) )
            print_unknown_data(ndo, p, "\n\t", caplen);
          break;
        case 142:
          ip6_print(ndo, p + 1, length - 1);
          break;
        case 204:
          ip_print(ndo, p + 1, length - 1);
          break;
        case 207:
          ppp_print(ndo, p + 1, length - 1);
          break;
        default:
          if ( !ndo->ndo_eflag )
            ndo->ndo_printf(ndo, "OSI NLPID 0x%02x unknown", *p);
          v6 = ", ";
          if ( ndo->ndo_eflag )
            v6 = "";
          ndo->ndo_printf(ndo, "%slength: %u", v6, length);
          if ( caplen > 1 )
            print_unknown_data(ndo, p, "\n\t", caplen);
          break;
      }
    }
    else
    {
      v5 = ", ";
      if ( ndo->ndo_eflag )
        v5 = "";
      ndo->ndo_printf(ndo, "%slength: %u", v5, length);
    }
  }
  else
  {
    ndo->ndo_printf(ndo, "|OSI");
  }
}