unsigned chdlc_if_print(netdissect_options *ndo, const struct pcap_pkthdr *h,
                        const unsigned char *p) {
  unsigned length = h->len;
  if (length < 4) {
    ndo->ndo_hexdump_line(ndo, "[|chdlc]");
    return (length);
  }
  return chdlc_print(ndo, p, h->caplen);
}