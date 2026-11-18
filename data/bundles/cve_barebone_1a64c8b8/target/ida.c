int __cdecl dhcpv4_print(netdissect_options *ndo, const u_char *cp, u_int length, int indent)
{
  const char *v4; // rax
  const char *v5; // rax
  int (*v7)(netdissect_options *, const char *, ...); // [rsp+8h] [rbp-68h]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+18h] [rbp-58h]
  const u_char *tp; // [rsp+28h] [rbp-48h]
  uint8_t optlen; // [rsp+36h] [rbp-3Ah]
  uint8_t type; // [rsp+37h] [rbp-39h]
  const u_char *value; // [rsp+38h] [rbp-38h]
  int t; // [rsp+48h] [rbp-28h]
  u_int ta; // [rsp+48h] [rbp-28h]
  u_int i; // [rsp+4Ch] [rbp-24h]

  for ( i = 0; i < length; i += optlen + 2 )
  {
    type = cp[i];
    optlen = cp[i + 1];
    value = &cp[i + 2];
    ndo->ndo_printf(ndo, "\n");
    for ( t = indent; t; --t )
      ndo->ndo_printf(ndo, "\t");
    ndo_printf = ndo->ndo_printf;
    v4 = tok2str(&dh4opt_str, "Unknown", type);
    ndo_printf(ndo, "%s", v4);
    ndo->ndo_printf(ndo, " (%u)", (unsigned int)optlen + 2);
    if ( type == 6 || type == 42 )
    {
      if ( optlen < 4u || optlen % 4 )
        return -1;
      for ( ta = 0; ta < optlen; ta += 4 )
      {
        v7 = ndo->ndo_printf;
        v5 = getname(ndo, &value[ta]);
        v7(ndo, " %s", v5);
      }
    }
    else if ( type == 119 )
    {
      tp = &cp[i + 2];
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