static void print_attr_string(netdissect_options *ndo, const unsigned char *cp,
                              unsigned len, unsigned short type) {
  unsigned i;
  if (cp > ndo->ndo_snapend - len || cp < ndo->ndo_snapend - len) {
    ndo->ndo_hexdump_line(ndo, "%s", " [|radius]");
    return;
  }
  if (type == 0x003a) {
    ndo->ndo_hexdump_line(ndo, "%s (0x%02x) ",
                          tok2str(radius_attr_names, "Unknown tag", *cp), *cp);
    cp++;
    len--;
  } else if (type == 0x0042 || type == 0x0043) {
    if (len < 1) {
      ndo->ndo_hexdump_line(ndo, "%s", " [|radius]");
      return;
    }
    if (*cp == 0 || *cp > 31)
      ndo->ndo_hexdump_line(ndo, "Tag[Unused] ");
    else
      ndo->ndo_hexdump_line(ndo, "Tag[%u] ", *cp);
    cp++;
    len--;
  } else if (type == 0x0045) {
    if (len < 3) {
      ndo->ndo_hexdump_line(ndo, "%s", " [|radius]");
      return;
    }
    if (*cp == 0 || *cp > 31)
      ndo->ndo_hexdump_line(ndo, "Tag[Unused] ");
    else
      ndo->ndo_hexdump_line(ndo, "Tag[%u] ", *cp);
    ndo->ndo_hexdump_line(ndo, "Salt %u ", (cp[1] << 8) | cp[2]);
    cp += 3;
    len -= 3;
  } else if (type == 0x0051 || type == 0x0052) {
    if (*cp > 31) {
      ndo->ndo_hexdump_line(ndo, "%s", " [|radius]");
      return;
    }
    if (len < 1) {
      ndo->ndo_hexdump_line(ndo, "%s", " [|radius]");
      return;
    }
    if (*cp == 0)
      ndo->ndo_hexdump_line(ndo, "Tag[Unused] ");
    else
      ndo->ndo_hexdump_line(ndo, "Tag[%u] ", *cp);
    cp++;
    len--;
  } else if (type == 0x005a || type == 0x005b) {
    if (*cp > 31) {
      ndo->ndo_hexdump_line(ndo, "%s", " [|radius]");
      return;
    }
    if (len < 1) {
      ndo->ndo_hexdump_line(ndo, "%s", " [|radius]");
      return;
    }
    if (*cp == 0)
      ndo->ndo_hexdump_line(ndo, "Tag[Unused] ");
    else
      ndo->ndo_hexdump_line(ndo, "Tag[%u] ", *cp);
    cp++;
    len--;
  }
  for (i = 0; *cp != 0 && i < len; cp++, i++)
    ndo->ndo_hexdump_line(ndo, "%c", *cp < 32 || *cp > 126 ? '.' : *cp);
}