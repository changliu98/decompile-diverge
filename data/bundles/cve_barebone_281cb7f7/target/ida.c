int __cdecl dhcpv6_print(netdissect_options *ndo, const u_char *cp, u_int length, int indent)
{
  const char *v4; // rax
  const char *v5; // rax
  int (*v7)(netdissect_options *, const char *, ...); // [rsp+8h] [rbp-68h]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+18h] [rbp-58h]
  const u_char *tp; // [rsp+28h] [rbp-48h]
  uint16_t optlen; // [rsp+34h] [rbp-3Ch]
  uint16_t type; // [rsp+36h] [rbp-3Ah]
  const u_char *value; // [rsp+38h] [rbp-38h]
  int t; // [rsp+48h] [rbp-28h]
  u_int ta; // [rsp+48h] [rbp-28h]
  u_int i; // [rsp+4Ch] [rbp-24h]

  for ( i = 0; i < length; i += optlen + 4 )
  {
    type = _byteswap_ushort(*(_WORD *)&cp[i]);
    optlen = _byteswap_ushort(*(_WORD *)&cp[i + 2]);
    value = &cp[i + 4];
    ndo->ndo_printf(ndo, "\n");
    for ( t = indent; t; --t )
      ndo->ndo_printf(ndo, "\t");
    ndo_printf = ndo->ndo_printf;
    v4 = tok2str(&dh6opt_str, "Unknown", type);
    ndo_printf(ndo, "%s", v4);
    ndo->ndo_printf(ndo, " (%u)", (unsigned int)optlen + 4);
    if ( type != 23 )
    {
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
        continue;
      }
      if ( type != 31 )
        continue;
    }
    if ( optlen % 16 )
    {
      ndo->ndo_printf(ndo, " %s", " (invalid)");
      return -1;
    }
    for ( ta = 0; ta < optlen; ta += 16 )
    {
      v7 = ndo->ndo_printf;
      v5 = getname6(ndo, &value[ta]);
      v7(ndo, " %s", v5);
    }
  }
  return 0;
}