int __cdecl dhcpv4_print(netdissect_options *ndo, const u_char *cp, u_int length, int indent)
{
  int (*ndo_printf)(netdissect_options *, const char *, ...);
  const u_char *value;
  const u_char *tp;
  uint8_t optlen;
  uint8_t type;
  u_int i, ta, t;

  for (i = 0; i < length; i += optlen + 2)
  {
    type = cp[i];
    optlen = cp[i + 1];
    value = &cp[i + 2];

    // Print newline and indentation
    ndo->ndo_printf(ndo, "\n");
    for (t = indent; t; --t)
      ndo->ndo_printf(ndo, "\t");

    // Cache function pointer to avoid repeated struct dereferences
    ndo_printf = ndo->ndo_printf;

    // Print option name and total length (optlen + 2 for type and length bytes)
    ndo_printf(ndo, "%s", tok2str(&dh4opt_str, "Unknown", type));
    ndo->ndo_printf(ndo, " (%u)", (unsigned int)optlen + 2);

    // Handle specific DHCPv4 options
    if (type == 6 || type == 42) // Option 6: DNS Server, Option 42: NTP Server
    {
      // Must be a multiple of 4 bytes (IPv4 addresses) and at least 4 bytes
      if (optlen < 4u || optlen % 4)
        return -1;

      for (ta = 0; ta < optlen; ta += 4)
      {
        ndo_printf(ndo, " %s", getname(ndo, &value[ta]));
      }
    }
    else if (type == 119) // Option 119: Domain Search List
    {
      tp = &cp[i + 2];
      while (tp < &value[optlen])
      {
        ndo->ndo_printf(ndo, " ");
        tp = ns_nprint(ndo, tp, &value[optlen]);
        if (!tp)
          return -1;
      }
    }
  }
  return 0;
}