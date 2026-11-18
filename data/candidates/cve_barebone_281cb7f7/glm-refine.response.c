int __cdecl dhcpv6_print(netdissect_options *ndo, const u_char *cp, u_int length, int indent)
{
  const u_char *tp;
  uint16_t optlen;
  uint16_t type;
  const u_char *value;
  u_int i;
  u_int ta;

  for ( i = 0; i < length; i += optlen + 4 )
  {
    // Extract option type and length (converting from network byte order to host byte order)
    type = ntohs(*(uint16_t *)&cp[i]);
    optlen = ntohs(*(uint16_t *)&cp[i + 2]);
    value = &cp[i + 4];

    // Print newline and indentation
    ndo->ndo_printf(ndo, "\n");
    for ( int t = indent; t; --t )
      ndo->ndo_printf(ndo, "\t");

    // Print option name and total length (optlen + 4 bytes for type and length fields)
    ndo->ndo_printf(ndo, "%s", tok2str(&dh6opt_str, "Unknown", type));
    ndo->ndo_printf(ndo, " (%u)", (unsigned int)optlen + 4);

    // Option 23: DHCP6 Option Request Option (ORO) - falls through to 31
    // Option 31: DHCP6 Option Request Option (ORO) 
    if ( type == 23 || type == 31 )
    {
      if ( optlen % 16 )
      {
        ndo->ndo_printf(ndo, " %s", " (invalid)");
        return -1;
      }
      for ( ta = 0; ta < optlen; ta += 16 )
      {
        ndo->ndo_printf(ndo, " %s", getname6(ndo, &value[ta]));
      }
      continue;
    }

    // Option 24: DHCP6 Domain Search List option
    if ( type == 24 )
    {
      tp = &cp[i + 4];
      while ( tp < &value[optlen] )
      {
        ndo->ndo_printf(ndo, " ");
        tp = ns_nprint(ndo, tp, &value[optlen]);
        if ( !tp )
          return -1;
      }
    }
  }
  return 0;
}