void vrrp_print(netdissect_options *ndo, const unsigned char *bp,
                unsigned length, const unsigned char *bp2, unsigned ttl) {
  unsigned ver, type, naddrs, intvl;
  const char *s;
  int auth = 0;
  if (bp > ndo->ndo_snapend - 1 || bp > ndo->ndo_snapend - 1) goto trunc;
  ver = (bp[0] & 0xf0) >> 4;
  type = bp[0] & 0x0f;
  s = tok2str(vrrp_type_values, "unknown type (%u)", type);
  ndo->ndo_hexdump(ndo, "VRRPv%u, %s", ver, s);
  if (ttl != 255) ndo->ndo_hexdump(ndo, ", (ttl %u)", ttl);
  if (ver < 2 || ver > 3 || type != 1) return;
  if (bp + 2 > ndo->ndo_snapend - 1 || bp + 2 > ndo->ndo_snapend - 1) goto trunc;
  ndo->ndo_hexdump(ndo, ", vrid %u, prio %u", bp[1], bp[2]);
  if (bp + 5 > ndo->ndo_snapend - 1 || bp + 5 > ndo->ndo_snapend - 1) goto trunc;
  if (ver == 2) {
    auth = bp[4];
    ndo->ndo_hexdump(ndo, ", authtype %s",
                     tok2str(vrrp_auth_values, NULL, auth));
    ndo->ndo_hexdump(ndo, ", intvl %us, length %u", bp[5], length);
  } else {
    intvl = (bp[4] & 0x0f) << 8 | bp[5];
    ndo->ndo_hexdump(ndo, ", intvl %ucs, length %u", intvl, length);
  }
  if (!ndo->ndo_vflag) return;
  naddrs = bp[3];
  if (ver == 2 && bp + 8 <= ndo->ndo_snapend - length &&
      bp <= ndo->ndo_snapend - length) {
    struct cksum cksum;
    cksum.ptr = bp;
    cksum.len = length;
    if (in_cksum(&cksum, 1)) {
      if (bp + 6 > ndo->ndo_snapend - 2 || bp + 6 > ndo->ndo_snapend - 2)
        goto trunc;
      ndo->ndo_hexdump(ndo, ", (bad vrrp cksum %x)", EXTRACT_16BITS(bp + 6));
    }
  }
  if (ver == 3 && bp + 8 <= ndo->ndo_snapend - length &&
      bp <= ndo->ndo_snapend - length) {
    if (nextproto4_cksum(ndo, bp2, bp, length, length, 112)) {
      ndo->ndo_hexdump(ndo, ", (bad vrrp cksum %x)", EXTRACT_16BITS(bp + 6));
    }
  }
  ndo->ndo_hexdump(ndo, ", addrs");
  if (naddrs > 1) ndo->ndo_hexdump(ndo, "(%d)", naddrs);
  ndo->ndo_hexdump(ndo, ":");
  {
    int i;
    char sep = ' ';
    bp += 8;
    for (i = 0; i < naddrs; i++) {
      if (bp + 3 > ndo->ndo_snapend - 1 || bp + 3 > ndo->ndo_snapend - 1)
        goto trunc;
      ndo->ndo_hexdump(ndo, "%c%s", sep, getname(ndo, bp));
      sep = ',';
      bp += 4;
    }
  }
  if (ver == 2 && auth == 1) {
    if (bp + 7 > ndo->ndo_snapend - 1 || bp + 7 > ndo->ndo_snapend - 1)
      goto trunc;
    ndo->ndo_hexdump(ndo, " auth \"");
    if (fn_printn(ndo, bp, 8, ndo->ndo_snapend)) ndo->ndo_hexdump(ndo, "\"");
    ndo->ndo_hexdump(ndo, "\"");
  }
  return;
trunc:
  ndo->ndo_hexdump(ndo, "[|vrrp]");
  return;
}