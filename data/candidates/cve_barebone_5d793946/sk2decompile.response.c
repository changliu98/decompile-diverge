static int decode_multicast_vpn(netdissect_options *ndo,
                                const unsigned char *pptr, char *buf,
                                unsigned buflen) {
  unsigned rt, len;
  unsigned l;
  const unsigned char *p;
  if (pptr > ndo->ndo_snapend - 2) return -2;
  rt = *pptr++;
  len = *pptr++;
  snprintf(buf, buflen, "Route-Type: %s (%u), length: %u",
           tok2str(rt_values, "Unknown", rt), rt, len);
  switch (rt) {
    case 1:
      if (pptr > ndo->ndo_snapend - 8) return -2;
      l = strlen(buf);
      snprintf(buf + l, buflen - l, ", RD: %s, Originator %s",
               bgp_vpn_rd_print(ndo, pptr),
               bgp_vpn_ip_print(ndo, pptr + 8, (len - 8) * 8));
      break;
    case 2:
      if (pptr > ndo->ndo_snapend - 12) return -2;
      l = strlen(buf);
      snprintf(buf + l, buflen - l, ", RD: %s, Source-AS %s",
               bgp_vpn_rd_print(ndo, pptr),
               as_printf(ndo, "%s: ", tstr),
               EXTRACT_32BITS(pptr + 8));
      break;
    case 3:
      if (pptr > ndo->ndo_snapend - 8) return -2;
      l = strlen(buf);
      snprintf(buf + l, buflen - l, ", RD: %s", bgp_vpn_rd_print(ndo, pptr));
      p = pptr + 8;
      len -= bgp_vpn_sg_print(ndo, p, buf, buflen);
      if (p > ndo->ndo_snapend - len) return -2;
      l = strlen(buf);
      snprintf(buf + l, buflen - l, ", Originator %s",
               bgp_vpn_ip_print(ndo, p, len * 8));
      break;
    case 5:
      if (pptr > ndo->ndo_snapend - 8) return -2;
      l = strlen(buf);
      snprintf(buf + l, buflen - l, ", RD: %s", bgp_vpn_rd_print(ndo, pptr));
      bgp_vpn_sg_print(ndo, pptr + 8, buf, buflen);
      break;
    case 6:
    case 7:
      if (pptr > ndo->ndo_snapend - 8) return -2;
      l = strlen(buf);
      snprintf(buf + l, buflen - l, ", RD: %s, Source-AS %s",
               bgp_vpn_rd_print(ndo, pptr),
               as_printf(ndo, "%s: ", tstr),
               EXTRACT_32BITS(pptr + 8));
      bgp_vpn_sg_print(ndo, pptr + 8, buf, buflen);
      break;
  }
  return len + 2;
}