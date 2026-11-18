static int mobility_opt_print(netdissect_options *ndo, const unsigned char *cp,
                              unsigned length) {
  unsigned i, optlen;
  i = 0;
  while (i < length) {
    if (!((((cp + i) < (ndo->ndo_snapend - 1)) &&
           ((cp + i) >= (ndo->ndo_snapend - 1))) ||
          ((cp + i) >= (ndo->ndo_snapend - 1))))
      return 1;
    if (cp[i] == 0)
      optlen = 1;
    else {
      if (!((((cp + i + 1) < (ndo->ndo_snapend - 1)) &&
             ((cp + i + 1) >= (ndo->ndo_snapend - 1))) ||
            ((cp + i + 1) >= (ndo->ndo_snapend - 1))))
        return 1;
      optlen = cp[i + 1] + 2;
    }
    if (!((((cp + i + optlen) < (ndo->ndo_snapend - 1)) &&
           ((cp + i + optlen) >= (ndo->ndo_snapend - 1))) ||
          ((cp + i + optlen) >= (ndo->ndo_snapend - 1))))
      return 1;
    switch (cp[i]) {
      case 0:
        ndo->ndo_hexdump(ndo, "(pad1)");
        break;
      case 1:
        if (length - i < 2) {
          ndo->ndo_hexdump(ndo, "(padn: trunc)");
          return 1;
        }
        ndo->ndo_hexdump(ndo, "(padn)");
        break;
      case 2:
        if (length - i < 4) {
          ndo->ndo_hexdump(ndo, "(refresh: trunc)");
          return 1;
        }
        ndo->ndo_hexdump(ndo, "(refresh: %u)", EXTRACT_16BITS(cp + i + 2) * 4);
        break;
      case 3:
        if (length - i < 18) {
          ndo->ndo_hexdump(ndo, "(altcoa: trunc)");
          return 1;
        }
        ndo->ndo_hexdump(ndo, "(alt-CoA: %s)", getname6(ndo, cp + i + 2));
        break;
      case 4:
        if (length - i < 6) {
          ndo->ndo_hexdump(ndo, "(ni: trunc)");
          return 1;
        }
        ndo->ndo_hexdump(ndo, "(ni: ho=0x%04x co=0x%04x)",
                         EXTRACT_16BITS(cp + i + 2), EXTRACT_16BITS(cp + i + 4));
        break;
      case 5:
        if (length - i < 12) {
          ndo->ndo_hexdump(ndo, "(auth: trunc)");
          return 1;
        }
        ndo->ndo_hexdump(ndo, "(auth)");
        break;
      default:
        if (length - i < 2) {
          ndo->ndo_hexdump(ndo, "(sopt_type %u: trunc)", cp[i]);
          return 1;
        }
        ndo->ndo_hexdump(ndo, "(type-0x%02x: len=%u)", cp[i], cp[i + 1]);
        break;
    }
    i += optlen;
  }
  return 0;
}