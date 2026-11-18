void __cdecl handle_mlppp(netdissect_options *ndo, const u_char *p, int length)
{
  char *v3; // rax
  unsigned int v4; // [rsp+Ch] [rbp-24h]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+10h] [rbp-20h]

  if ( !ndo->ndo_eflag )
    ndo->ndo_printf(ndo, "MLPPP, ");
  ndo_printf = ndo->ndo_printf;
  v4 = EXTRACT_16BITS(p) & 0xFFF;
  v3 = bittok2str(&ppp_ml_flag_values, "none", *p & 0xC0);
  ndo_printf(ndo, "seq 0x%03x, Flags [%s], length %u", v4, v3, (unsigned int)length);
}