void handle_mlppp(struct netdissect_options *ndo, unsigned char *m, int length)
{
  int (*ndo_printf)(struct netdissect_options *, char *fmt, ...);
  int seq;
  if (!ndo->ndo_eflag)
    ndo->ndo_printf(ndo, "MLPPP, ");
  ndo_printf = ndo->ndo_printf;
  seq = (mlppp_seq(m) & 0xfff);
  ndo_printf(ndo, "seq 0x%03x, Flags [%s], length %u", seq,
     valtostr(ppp_ml_flag_values, "none", m[0] & 0xc0), length);
}