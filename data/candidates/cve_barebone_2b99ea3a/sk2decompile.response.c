int frag6_print(netdissect_options *ndo, const unsigned char *bp,
                const unsigned char *ep) {
  const struct frag6_hdr *fh = (const struct frag6_hdr *)bp;
  if (bp + 2 > ndo->ndo_snapend - 2 || bp + 2 > ep) {
    ndo->ndo_vprintf(ndo, "[|frag]");
    return -1;
  }
  if (ndo->ndo_vflag)
    ndo->ndo_vprintf(ndo, "frag (0x%08x:%d|%ld)", EXTRACT_32BITS(&fh->fh_id),
                     EXTRACT_16BITS(&fh->fh_off) & 0xfff8,
                     (long)EXTRACT_16BITS(&fh->fh_res) + 40 - (bp - ep) - 8);
  else
    ndo->ndo_vprintf(ndo, "frag (%d|%ld)", EXTRACT_16BITS(&fh->fh_off) & 0xfff8,
                     (long)EXTRACT_16BITS(&fh->fh_res) + 40 - (bp - ep) - 8);
  if (EXTRACT_16BITS(&fh->fh_off) & 0xfff8) return -1;
  ndo->ndo_vprintf(ndo, " ");
  return 8;
}