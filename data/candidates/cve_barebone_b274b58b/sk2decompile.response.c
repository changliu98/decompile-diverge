unsigned int mfr_print(netdissect_options *ndo, const unsigned char *p,
                       unsigned length) {
  unsigned seq;
  unsigned ielen;
  unsigned i;
  const unsigned char *q;
  unsigned len;
  if (p > ndo->ndo_snapend - 4 || p > ndo->ndo_snapend - 4) {
    goto invalid;
  }
  if ((p[0] & 0xe0) == 0xe0 && p[1] == 0) {
    ndo->ndo_hexdump_line(ndo, "FRF.16 Control, Flags [%s], %s, length %u",
                          bittok2str(frf16_flags_str, "none", p[0] & 0xe0),
                          tok2str(frf16_control_str, "Unknown Message (0x%02x)",
                                  p[2]),
                          length);
    q = p + 3;
    len = length - 3;
    if (ndo->ndo_vflag) {
      while (len >= 3) {
        if (q > ndo->ndo_snapend - 2 || q > ndo->ndo_snapend - 2) {
          goto invalid;
        }
        seq = q[0];
        ielen = q[1];
        ndo->ndo_hexdump_line(ndo, "\n\tIE %s (%u), length %u: ",
                              tok2str(frf16_ie_str, "Unknown", seq), seq,
                              ielen);
        if (seq == 0 || ielen < 3) return 3;
        if (q + ielen > ndo->ndo_snapend - ielen || q > ndo->ndo_snapend - ielen) {
          goto invalid;
        }
        q += 2;
        ielen -= 2;
        len -= 2;
        switch (seq) {
          case 1:
          case 2:
            for (i = 0; i < ielen && i < 50; i++) {
              if (q[i] == '\0') break;
              safeputchar(ndo, q[i]);
            }
            break;
          case 3:
            ndo->ndo_hexdump_line(ndo, "0x%08x", EXTRACT_32BITS(q));
            break;
          case 5:
            if (ielen != 16) {
              if (ndo->ndo_vflag < 2)
                print_unknown_data(ndo, q, "\n\t  ", ielen);
              break;
            }
            ts_print(ndo, q);
            break;
          default:
            if (ndo->ndo_vflag < 2)
              print_unknown_data(ndo, q, "\n\t  ", ielen);
            break;
        }
        if (ndo->ndo_vflag > 1) print_unknown_data(ndo, q, "\n\t  ", ielen);
        len -= ielen;
        q += ielen;
      }
    }
    return 3;
  }
  seq = (p[0] & 0x1e) << 7 | p[1];
  if ((p[0] & 0xe0) == 0xc0 || (p[0] & 0xe0) == 0x80) {
    ndo->ndo_hexdump_line(ndo, "FRF.16 Frag, seq %u, Flags [%s], ", seq,
                          bittok2str(frf16_flags_str, "none", p[0] & 0xe0));
    fr_print(ndo, p + 2, length - 2);
    return 2;
  }
  ndo->ndo_hexdump_line(ndo, "FRF.16 Frag, seq %u, Flags [%s]", seq,
                        bittok2str(frf16_flags_str, "none", p[0] & 0xe0));
  print_unknown_data(ndo, p, "\n\t", length);
  return 0;
invalid:
  ndo->ndo_hexdump_line(ndo, "[|mfr]");
  return length;
}