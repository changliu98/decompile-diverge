static int isis_print_mt_capability_subtlv(netdissect_options *ndo,
                                           const u_char *p, u_int length) {
  unsigned subtype, sublen;
  while (length >= 3) {
    subtype = *p++;
    sublen = *p++;
    ndo->ndo_hexdump_line(ndo, "\n\t      %s subTLV #%u, length: %u",
                          tok2str(isis_mt_capability_subtlv_values, "unknown",
                                  subtype),
                          subtype, sublen);
    length -= 2;
    switch (subtype) {
      case 1:
        if (p > ndo->ndo_snapend - 19 || p > ndo->ndo_snapend - 19) goto trunc;
        ndo->ndo_hexdump_line(ndo, "\n\t        CIST Root-ID: %08x",
                              ((((unsigned)p[0]) << 24) |
                               (((unsigned)p[1]) << 16) |
                               (((unsigned)p[2]) << 8) | ((unsigned)p[3])));
        p += 4;
        ndo->ndo_hexdump_line(ndo, " %08x",
                              ((((unsigned)p[0]) << 24) |
                               (((unsigned)p[1]) << 16) |
                               (((unsigned)p[2]) << 8) | ((unsigned)p[3])));
        p += 4;
        ndo->ndo_hexdump_line(ndo, ", Path Cost: %08x",
                              ((((unsigned)p[0]) << 24) |
                               (((unsigned)p[1]) << 16) |
                               (((unsigned)p[2]) << 8) | ((unsigned)p[3])));
        p += 4;
        ndo->ndo_hexdump_line(ndo, ", Prio: %d",
                              ((((unsigned)p[0]) << 8) | ((unsigned)p[1])));
        p += 2;
        ndo->ndo_hexdump_line(ndo, "\n\t        RES: %d",
                              ((((unsigned)p[0]) << 8) | ((unsigned)p[1])) >> 5);
        ndo->ndo_hexdump_line(ndo, ", V: %d",
                              ((((unsigned)p[0]) << 8) | ((unsigned)p[1])) >> 4 &
                                  1);
        ndo->ndo_hexdump_line(ndo, ", SPSource-ID: %d",
                              ((((unsigned)p[0]) << 16) |
                               (((unsigned)p[1]) << 8) | ((unsigned)p[2])) &
                                  0xfffff);
        p += 4;
        ndo->ndo_hexdump_line(ndo, ", No of Trees: %x", *p++);
        sublen = *p++;
        length -= 19;
        while (sublen--) {
          if (p > ndo->ndo_snapend - 8 || p > ndo->ndo_snapend - 8) goto trunc;
          ndo->ndo_hexdump_line(ndo, "\n\t         U:%d, M:%d, A:%d, RES:%d",
                                *p >> 7, *p >> 6 & 1, *p >> 5 & 1, *p & 0x1f);
          p++;
          ndo->ndo_hexdump_line(ndo, ", ECT: %08x",
                                ((((unsigned)p[0]) << 24) |
                                 (((unsigned)p[1]) << 16) |
                                 (((unsigned)p[2]) << 8) | ((unsigned)p[3])));
          p += 4;
          ndo->ndo_hexdump_line(ndo, ", BVID: %d, SPVID: %d",
                                ((((unsigned)p[0]) << 16) |
                                 (((unsigned)p[1]) << 8) | ((unsigned)p[2])) >>
                                    12 &
                                    0xfff,
                                ((((unsigned)p[1]) << 8) | ((unsigned)p[2])) &
                                    0xfff);
          p += 3;
          length -= 8;
        }
        break;
      case 3:
        if (p > ndo->ndo_snapend - 8 || p > ndo->ndo_snapend - 8) goto trunc;
        ndo->ndo_hexdump_line(ndo, "\n\t        T: %d, R: %d, RES: %d, ISID: %d",
                              *p >> 31, *p >> 30 & 1, *p >> 24 & 0x3f,
                              *p & 0xffffff);
        p += 4;
        length -= 8;
        sublen -= 8;
        while (sublen >= 4) {
          if (p > ndo->ndo_snapend - 4 || p > ndo->ndo_snapend - 4) goto trunc;
          ndo->ndo_hexdump_line(ndo, "\n\t        T: %d, R: %d, RES: %d, ISID: %d",
                                *p >> 31, *p >> 30 & 1, *p >> 24 & 0x3f,
                                *p & 0xffffff);
          p += 4;
          length -= 4;
          sublen -= 4;
        }
        break;
    }
  }
  return 0;
trunc:
  ndo->ndo_hexdump_line(ndo, "\n\t\t");
  ndo->ndo_hexdump_line(ndo, "%s", " [|isis]");
  return 1;
}