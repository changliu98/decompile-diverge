unsigned int chdlc_print(netdissect_options *ndo, const unsigned char *p,
                         unsigned int length) {
  unsigned int ethertype = EXTRACT_16BITS(p + 2);
  if (ndo->ndo_eflag)
    ndo->ndo_line_printf(
        ndo, "%s, ethertype %s (0x%04x), length %u: ",
        tok2str(chdlc_type_values, "0x%02x", p[0]),
        tok2str(chdlc_ethertype_values, "Unknown", ethertype), ethertype,
        length);
  p += 4;
  length -= 4;
  switch (ethertype) {
    case 0x0800:
      ip_print(ndo, p, length);
      break;
    case 0x880d:
      chdlc_slarp_print(ndo, p, length);
      break;
    case 0x86dd:
      ip6_print(ndo, p, length);
      break;
    case 0x8847:
    case 0x8848:
      mpls_print(ndo, p, length);
      break;
    case 0xfeff:
      if (p[1] == 0x81 || p[1] == 0x82 || p[1] == 0x83)
        isoclns_print(ndo, p + 1, length - 1, ndo->ndo_snapend - p - 1);
      else
        isoclns_print(ndo, p, length, ndo->ndo_snapend - p);
      break;
    default:
      if (!ndo->ndo_eflag)
        ndo->ndo_line_printf(ndo, "unknown CHDLC protocol (0x%04x)", ethertype);
      break;
  }
  return 4;
}