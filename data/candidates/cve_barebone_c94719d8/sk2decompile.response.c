void ripng_print(netdissect_options *ndo, const u_char *p, unsigned length) {
  const struct ripng_header *rp;
  unsigned caplen;
  unsigned n;
  int printed;
  if (p > ndo->ndo_snapend) return;
  caplen = length;
  if (caplen > ndo->ndo_snapend - p) caplen = ndo->ndo_snapend - p;
  if (caplen < sizeof(*rp)) return;
  caplen -= sizeof(*rp);
  rp = (const struct ripng_header *)p;
  switch (rp->rip_cmd) {
    case 1:
      n = length / 20;
      if (n == 1 && rp->rip_family == 16 && rp->rip_reserved1 == 0 &&
          rp->rip_reserved2 == 0 && rp->rip_reserved3 == 0 &&
          rp->rip_reserved4 == 0) {
        ndo->ndo_hexdump(ndo, " ripng-req dump");
        break;
      }
      if (n * 20 == length - 4)
        ndo->ndo_hexdump(ndo, " ripng-req %d:", n);
      else
        ndo->ndo_hexdump(ndo, " ripng-req %d[%u]:", n, length);
      p += sizeof(*rp);
      caplen -= sizeof(*rp);
      printed = 0;
      while (caplen >= sizeof(*rp)) {
        if (ndo->ndo_vflag > 1)
          ndo->ndo_hexdump(ndo, "\n\t");
        else
          ndo->ndo_hexdump(ndo, " ");
        rip6_entry_print(ndo, p, 0);
        caplen -= sizeof(*rp);
        p += sizeof(*rp);
        printed = 1;
      }
      break;
    case 2:
      n = length / 20;
      if (n * 20 == length - 4)
        ndo->ndo_hexdump(ndo, " ripng-resp %d:", n);
      else
        ndo->ndo_hexdump(ndo, " ripng-resp %d[%u]:", n, length);
      p += sizeof(*rp);
      caplen -= sizeof(*rp);
      printed = 0;
      while (caplen >= sizeof(*rp)) {
        if (ndo->ndo_vflag > 1)
          ndo->ndo_hexdump(ndo, "\n\t");
        else
          ndo->ndo_hexdump(ndo, " ");
        rip6_entry_print(ndo, p, p->rip_metric);
        caplen -= sizeof(*rp);
        p += sizeof(*rp);
        printed = 1;
      }
      if (printed) ndo->ndo_hexdump(ndo, "[|ripng]");
      break;
    default:
      ndo->ndo_hexdump(ndo, " ripng-%d ?? %u", rp->rip_cmd, length);
      break;
  }
  if (rp->rip_version != 1)
    ndo->ndo_hexdump(ndo, " [vers %d]", rp->rip_version);
}