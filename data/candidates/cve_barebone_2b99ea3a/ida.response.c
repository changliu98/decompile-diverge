int __cdecl frag6_print(netdissect_options *ndo, const u_char *bp_0, const u_char *bp2)
{
  uint16_t v3; // ax
  uint16_t v4; // ax
  unsigned int v6; // [rsp+Ch] [rbp-54h]
  int (*v7)(netdissect_options *, const char *, ...); // [rsp+10h] [rbp-50h]
  uint32_t v8; // [rsp+20h] [rbp-40h]
  unsigned int v9; // [rsp+24h] [rbp-3Ch]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+28h] [rbp-38h]

  if ( ndo->ndo_snapend - 2 <= ndo->ndo_snapend && bp_0 + 2 <= ndo->ndo_snapend - 2 )
  {
    if ( ndo->ndo_vflag )
    {
      ndo_printf = ndo->ndo_printf;
      v8 = EXTRACT_32BITS(bp_0 + 4);
      v9 = EXTRACT_16BITS(bp_0 + 2) & 0xFFF8;
      v3 = EXTRACT_16BITS(bp2 + 4);
      ndo_printf(ndo, "frag (0x%08x:%d|%ld)", v8, v9, v3 + 40LL - (bp_0 - bp2) - 8);
    }
    else
    {
      v7 = ndo->ndo_printf;
      v6 = EXTRACT_16BITS(bp_0 + 2) & 0xFFF8;
      v4 = EXTRACT_16BITS(bp2 + 4);
      v7(ndo, "frag (%d|%ld)", v6, v4 + 40LL - (bp_0 - bp2) - 8);
    }
    if ( (EXTRACT_16BITS(bp_0 + 2) & 0xFFF8) != 0 )
    {
      return -1;
    }
    else
    {
      ndo->ndo_printf(ndo, " ");
      return 8;
    }
  }
  else
  {
    ndo->ndo_printf(ndo, "[|frag]");
    return -1;
  }
}