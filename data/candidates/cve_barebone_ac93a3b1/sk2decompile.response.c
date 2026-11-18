static int mp_dss_print(netdissect_options *ndo, const unsigned char *p,
                        unsigned length, unsigned flags) {
  const unsigned char *cp;
  if (length != mp_dss_len(p, 1) && length != mp_dss_len(p, 0)) return 0;
  if (flags & 0x02) return 0;
  cp = p;
  cp += 3;
  if (*cp & 0x10) ndo->ndo_hexdump_line(ndo, " fin");
  cp++;
  if (*cp & 0x01) {
    ndo->ndo_hexdump_line(ndo, " ack ");
    if (*cp & 0x02) {
      ndo->ndo_hexdump_line(ndo, "%lu", EXTRACT_64BITS(cp));
      cp += 8;
    } else {
      ndo->ndo_hexdump_line(ndo, "%u", EXTRACT_32BITS(cp));
      cp += 4;
    }
  }
  if (*cp & 0x04) {
    ndo->ndo_hexdump_line(ndo, " seq ");
    if (*cp & 0x08) {
      ndo->ndo_hexdump_line(ndo, "%lu", EXTRACT_64BITS(cp));
      cp += 8;
    } else {
      ndo->ndo_hexdump_line(ndo, "%u", EXTRACT_32BITS(cp));
      cp += 4;
    }
    ndo->ndo_hexdump_line(ndo, " subseq %u", EXTRACT_32BITS(cp));
    cp += 4;
    ndo->ndo_hexdump_line(ndo, " len %u", EXTRACT_16BITS(cp));
    cp += 2;
    if (length == mp_dss_len(p, 1))
      ndo->ndo_hexdump_line(ndo, " csum 0x%x", EXTRACT_16BITS(cp));
  }
  return 1;
}