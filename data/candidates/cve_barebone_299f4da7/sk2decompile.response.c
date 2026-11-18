static void handle_mlppp(netdissect_options *ndo, const unsigned char *p,
                         unsigned length) {
  if (!ndo->ndo_qflag) (void)ndo->ndo_vprintf(ndo, "MLPPP, ");
  ndo->ndo_vprintf(ndo, "seq 0x%03x, Flags [%s], length %u",
                   EXTRACT_16BITS(p) & 0x0fff,
                   bittok2str(mlppp_flags_values, "none", p[0] & 0xc0), length);
}