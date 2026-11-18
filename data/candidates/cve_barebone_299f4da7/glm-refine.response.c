void __cdecl handle_mlppp(netdissect_options *ndo, const u_char *p, int length)
{
  uint16_t seq;
  const char *flags_str;

  if (!ndo->ndo_eflag)
    ndo->ndo_printf(ndo, "MLPPP, ");

  seq = EXTRACT_16BITS(p) & 0x0FFF;
  flags_str = bittok2str(&ppp_ml_flag_values, "none", *p & 0xC0);
  
  ndo->ndo_printf(ndo, "seq 0x%03x, Flags [%s], length %u", seq, flags_str, length);
}