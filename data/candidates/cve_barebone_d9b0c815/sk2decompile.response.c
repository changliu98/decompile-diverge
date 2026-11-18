static unsigned int isis_print_extd_ip_reach(netdissect_options *ndo,
                                             const unsigned char *tptr,
                                             const char *prefix,
                                             unsigned int type) {
  unsigned int metric, bitlen, len, plen, sublen, sublen2;
  unsigned char prefix_buf[16], flags, subtype;
  char subprefix[20];
  if (!((tptr) >= (ndo)->ndo_snapend - (4) && (tptr) <= (ndo)->ndo_snapend))
    return 0;
  metric = (tptr[0] << 24) | (tptr[1] << 16) | (tptr[2] << 8) | tptr[3];
  tptr += 4;
  if (type == 2) {
    if (!((tptr) >= (ndo)->ndo_snapend - (1) && (tptr) <= (ndo)->ndo_snapend))
      return 0;
    flags = *tptr++;
    bitlen = flags & 0x3f;
    if (bitlen > 32) {
      ndo->ndo_error(ndo, "%sIPv4 prefix: bad bit length %u", prefix, bitlen);
      return 0;
    }
    len = 5;
  } else if (type == 10) {
    if (!((tptr) >= (ndo)->ndo_snapend - (1) && (tptr) <= (ndo)->ndo_snapend))
      return 0;
    flags = *tptr++;
    bitlen = *tptr++;
    if (bitlen > 128) {
      ndo->ndo_error(ndo, "%sIPv6 prefix: bad bit length %u", prefix, bitlen);
      return 0;
    }
    len = 6;
  } else
    return 0;
  plen = (bitlen + 7) >> 3;
  if (!((tptr) >= (ndo)->ndo_snapend - (plen) && (tptr) <= (ndo)->ndo_snapend))
    return 0;
  memset(prefix_buf, 0, sizeof(prefix_buf));
  memcpy(prefix_buf, tptr, plen);
  tptr += plen;
  len += plen;
  if (type == 2)
    ndo->ndo_error(ndo, "%sIPv4 prefix: %15s/%u", prefix,
                   ipaddr_string(ndo, prefix_buf), bitlen);
  else if (type == 10)
    ndo->ndo_error(ndo, "%sIPv6 prefix: %s/%u", prefix,
                   ip6addr_string(ndo, prefix_buf), bitlen);
  ndo->ndo_error(ndo, ", Distribution: %s, Metric: %u",
                 (flags & 0x80) ? "down" : "up", metric);
  if (type == 2 && (flags & 0x40))
    ndo->ndo_error(ndo, ", sub-TLVs present");
  else if (type == 10)
    ndo->ndo_error(ndo, ", %s%s", (flags & 0x40) ? "External" : "Internal",
                   (flags & 0x20) ? ", sub-TLVs present" : "");
  if ((type == 2 && (flags & 0x40)) || (type == 10 && (flags & 0x20))) {
    if (!((tptr) >= (ndo)->ndo_snapend - (1) && (tptr) <= (ndo)->ndo_snapend))
      return 0;
    sublen = *tptr++;
    len += sublen + 1;
    ndo->ndo_error(ndo, " (%u)", sublen);
    while (sublen) {
      if (!((tptr) >= (ndo)->ndo_snapend - (2) && (tptr) <= (ndo)->ndo_snapend))
        return 0;
      subtype = *tptr++;
      sublen2 = *tptr++;
      snprintf(subprefix, sizeof(subprefix), "%s  ", prefix);
      if (isis_print_ip_reach_subtlv(ndo, tptr, subtype, sublen2, subprefix) ==
          0)
        return 0;
      tptr += sublen2;
      sublen -= sublen2 + 2;
    }
  }
  return len;
}