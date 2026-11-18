int __cdecl mobility_opt_print(netdissect_options *ndo, const u_char *bp_0, const unsigned int len)
{
  uint16_t v3; // ax
  const char *v4; // rax
  uint16_t v5; // ax
  unsigned int v7; // [rsp+14h] [rbp-5Ch]
  int (*v8)(netdissect_options *, const char *, ...); // [rsp+18h] [rbp-58h]
  int (*v9)(netdissect_options *, const char *, ...); // [rsp+28h] [rbp-48h]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+38h] [rbp-38h]
  unsigned int optlen; // [rsp+4Ch] [rbp-24h]
  unsigned int i; // [rsp+50h] [rbp-20h]

  i = 0;
  while ( 2 )
  {
    if ( i >= len )
      return 0;
    if ( ndo->ndo_snapend - 1 > ndo->ndo_snapend || &bp_0[i] > ndo->ndo_snapend - 1 )
      return 1;
    if ( bp_0[i] )
    {
      if ( i + 1 >= len || ndo->ndo_snapend - 1 > ndo->ndo_snapend || &bp_0[i + 1] > ndo->ndo_snapend - 1 )
        return 1;
      optlen = bp_0[i + 1] + 2;
    }
    else
    {
      optlen = 1;
    }
    if ( optlen + i > len || ndo->ndo_snapend - 1 > ndo->ndo_snapend || &bp_0[optlen + i] > ndo->ndo_snapend - 1 )
      return 1;
    switch ( bp_0[i] )
    {
      case 0u:
        ndo->ndo_printf(ndo, "(pad1)");
        goto LABEL_38;
      case 1u:
        if ( len - i < 2 )
        {
          ndo->ndo_printf(ndo, "(padn: trunc)");
          return 1;
        }
        ndo->ndo_printf(ndo, "(padn)");
        goto LABEL_38;
      case 2u:
        if ( len - i < 4 )
        {
          ndo->ndo_printf(ndo, "(refresh: trunc)");
          return 1;
        }
        ndo_printf = ndo->ndo_printf;
        v3 = EXTRACT_16BITS(&bp_0[i + 2]);
        ndo_printf(ndo, "(refresh: %u)", 4 * (unsigned int)v3);
        goto LABEL_38;
      case 3u:
        if ( len - i < 0x12 )
        {
          ndo->ndo_printf(ndo, "(altcoa: trunc)");
          return 1;
        }
        v9 = ndo->ndo_printf;
        v4 = getname6(ndo, &bp_0[i + 2]);
        v9(ndo, "(alt-CoA: %s)", v4);
        goto LABEL_38;
      case 4u:
        if ( len - i < 6 )
        {
          ndo->ndo_printf(ndo, "(ni: trunc)");
          return 1;
        }
        v8 = ndo->ndo_printf;
        v7 = EXTRACT_16BITS(&bp_0[i + 2]);
        v5 = EXTRACT_16BITS(&bp_0[i + 4]);
        v8(ndo, "(ni: ho=0x%04x co=0x%04x)", v7, v5);
        goto LABEL_38;
      case 5u:
        if ( len - i < 0xC )
        {
          ndo->ndo_printf(ndo, "(auth: trunc)");
          return 1;
        }
        ndo->ndo_printf(ndo, "(auth)");
        goto LABEL_38;
      default:
        if ( len - i >= 2 )
        {
          ndo->ndo_printf(ndo, "(type-0x%02x: len=%u)", bp_0[i], bp_0[i + 1]);
LABEL_38:
          i += optlen;
          continue;
        }
        ndo->ndo_printf(ndo, "(sopt_type %u: trunc)", bp_0[i]);
        return 1;
    }
  }
}