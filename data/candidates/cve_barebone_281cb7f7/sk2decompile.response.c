int dhcpv6_print(netdissect_options *ndo, const unsigned char *cp,
                 unsigned length, int indent) {
  unsigned i;
  unsigned type;
  unsigned len;
  unsigned j;
  const unsigned char *data;
  const unsigned char *end;
  for (i = 0; i < length; i += len + 4) {
    type = (cp[i] << 8) | cp[i + 1];
    len = (cp[i + 2] << 8) | cp[i + 3];
    data = cp + i + 4;
    end = data + len;
    ndo->ndo_vprintf(ndo, "\n");
    for (j = indent; j; j--) ndo->ndo_vprintf(ndo, "\t");
    ndo->ndo_vprintf(ndo, "%s", tok2str(dhcpv6_options, "Unknown", type));
    ndo->ndo_vprintf(ndo, " (%u)", len + 4);
    switch (type) {
      case 23:
      case 24:
        if (len % 16) {
          ndo->ndo_vprintf(ndo, " %s", " (invalid)");
          return -1;
        }
        for (j = 0; j < len; j += 16)
          ndo->ndo_vprintf(ndo, " %s", getname6(ndo, data + j));
        break;
      case 31:
        if (len % 16) {
          ndo->ndo_vprintf(ndo, " %s", " (invalid)");
          return -1;
        }
        for (j = 0; j < len; j += 16)
          ndo->ndo_vprintf(ndo, " %s", getname6(ndo, data + j));
        break;
    }
  }
  return 0;
}