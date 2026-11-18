int dhcpv4_print(netdissect_options *ndo, const unsigned char *p, unsigned len,
                 int indent) {
  unsigned i;
  unsigned optlen;
  unsigned opt;
  const unsigned char *optval;
  unsigned j;
  for (i = 0; i < len; i += optlen + 2) {
    opt = p[i];
    optlen = p[i + 1];
    optval = p + i + 2;
    ndo->ndo_vprintf(ndo, "\n");
    for (j = indent; j > 0; j--) ndo->ndo_vprintf(ndo, "\t");
    ndo->ndo_vprintf(ndo, "%s", tok2str(dhcpv4_options, "Unknown", opt));
    ndo->ndo_vprintf(ndo, " (%u)", optlen + 2);
    if (opt == 6 || opt == 42) {
      unsigned k;
      if (optlen < 4 || optlen % 4) return -1;
      for (k = 0; k < optlen; k += 4)
        ndo->ndo_vprintf(ndo, " %s", getname(ndo, optval + k));
    } else if (opt == 119) {
      const unsigned char *q = optval;
      while (q < optval + optlen) {
        ndo->ndo_vprintf(ndo, " ");
        q = ns_nprint(ndo, q, optval + optlen);
        if (q == NULL) return -1;
      }
    }
  }
  return 0;
}