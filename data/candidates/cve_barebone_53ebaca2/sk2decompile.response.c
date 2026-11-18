void isakmp_rfc3948_print(netdissect_options *ndo, const unsigned char *p,
                          unsigned length, const u_short *fingerprint) {
  unsigned ip_hdrlen;
  unsigned ip_version;
  unsigned ip_hdrlen_inner;
  if (length == 1 && p[0] == 0xff) {
    ndo->ndo_hexdump_line(ndo, "isakmp-nat-keep-alive");
    return;
  }
  if (length < 4) {
    ndo->ndo_hexdump_line(ndo, "[|isakmp]");
    return;
  }
  if (p[0] == 0 && p[1] == 0 && p[2] == 0 && p[3] == 0) {
    ndo->ndo_hexdump_line(ndo, "NONESP-encap: ");
    isakmp_print(ndo, p + 4, length - 4, fingerprint);
    return;
  }
  ndo->ndo_hexdump_line(ndo, "UDP-encap: ");
  ip_hdrlen =
      esp_print(ndo, p, length, fingerprint, &ip_version, &ip_hdrlen_inner);
  if (ip_hdrlen > 0) {
    p += ip_hdrlen;
    length -= ip_hdrlen + ip_hdrlen_inner;
    ip_hdrlen = ip_version & 0xff;
    ip_print_inner(ndo, p, length, ip_hdrlen, fingerprint);
  }
}