void arp_print(netdissect_options *ndo, const unsigned char *bp, unsigned length,
               unsigned caplen) {
  const struct arphdr *ap;
  unsigned short hrd, pro, op;
  unsigned short hrd_len;
  if (bp > ndo->ndo_snapend - 8 || bp + (8) > ndo->ndo_snapend) {
    ndo->ndo_vprintf(ndo, "%s", "[|ARP]");
    return;
  }
  ap = (const struct arphdr *)bp;
  hrd = EXTRACT_16BITS(&ap->ar_hrd);
  pro = EXTRACT_16BITS(&ap->ar_pro);
  op = EXTRACT_16BITS(&ap->ar_op);
  if (hrd == 15)
    hrd_len = 1;
  else if (hrd == 19) {
    atmarp_print(ndo, bp, length, caplen);
    return;
  } else
    hrd_len = 0;
  if (bp + ap->ar_hln > ndo->ndo_snapend ||
      bp + ap->ar_hln + ap->ar_pln > ndo->ndo_snapend) {
    ndo->ndo_vprintf(ndo, "%s", "[|ARP]");
    ndo->ndo_hexdump(ndo, bp, length);
    return;
  }
  if (!ndo->ndo_vflag) ndo->ndo_vprintf(ndo, "ARP, ");
  if ((pro == 2048 || pro == 4096) && ap->ar_hln == 4 && ap->ar_pln &&
      !ndo->ndo_eflag) {
  } else {
    ndo->ndo_vprintf(ndo, "%s (len %u), %s (len %u)",
                     tok2str(arp_hrd, "Unknown Hardware (%u)", hrd), ap->ar_pln,
                     tok2str(arp_pro, "Unknown Protocol (0x%04x)", pro),
                     ap->ar_hln);
    if (!ndo->ndo_eflag) goto out;
  }
  ndo->ndo_vprintf(ndo, "%s%s ", ndo->ndo_eflag ? ", " : "",
                   tok2str(arp_op, "Unknown (%u)", op));
  switch (op) {
    case 1:
      ndo->ndo_vprintf(ndo, "who-has %s",
                       getname(ndo, bp + ap->ar_hln + ap->ar_pln));
      if (isnonzero(bp + ap->ar_hln + ap->ar_pln, ap->ar_pln))
        ndo->ndo_vprintf(ndo, " (%s)",
                         linkaddr_string(ndo, bp + ap->ar_hln + ap->ar_pln,
                                         hrd_len, ap->ar_pln));
      ndo->ndo_vprintf(ndo, " tell %s", getname(ndo, bp + ap->ar_hln));
      break;
    case 2:
      ndo->ndo_vprintf(ndo, "%s is-at %s", getname(ndo, bp + ap->ar_hln),
                       linkaddr_string(ndo, bp + 8, hrd_len, ap->ar_pln));
      break;
    case 3:
      ndo->ndo_vprintf(ndo, "who-is %s tell %s",
                       linkaddr_string(ndo, bp + ap->ar_hln + ap->ar_pln,
                                       hrd_len, ap->ar_pln),
                       linkaddr_string(ndo, bp + 8, hrd_len, ap->ar_pln));
      break;
    case 4:
      ndo->ndo_vprintf(ndo, "%s at %s",
                       linkaddr_string(ndo, bp + ap->ar_hln + ap->ar_pln,
                                       hrd_len, ap->ar_pln),
                       getname(ndo, bp + ap->ar_hln));
      break;
    case 8:
      ndo->ndo_vprintf(ndo, "who-is %s tell %s",
                       linkaddr_string(ndo, bp + ap->ar_hln + ap->ar_pln,
                                       hrd_len, ap->ar_pln),
                       linkaddr_string(ndo, bp + 8, hrd_len, ap->ar_pln));
      break;
    case 9:
      ndo->ndo_vprintf(ndo, "%s at %s",
                       linkaddr_string(ndo, bp + 8, hrd_len, ap->ar_pln),
                       getname(ndo, bp + ap->ar_hln));
      break;
    default:
      ndo->ndo_hexdump(ndo, bp, caplen);
      return;
  }
out:
  ndo->ndo_vprintf(ndo, ", length %u", length);
}