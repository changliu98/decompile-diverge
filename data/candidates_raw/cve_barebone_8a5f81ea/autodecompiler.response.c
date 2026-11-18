static int
pktap_print(netdissect_options *ndo,
            register struct pktap_header *pktaphdr, register u_char *cp)
{
 register unsigned int caplen = pktaphdr->ph_caplen;
 register unsigned int length = pktaphdr->ph_len;
 register unsigned int hdrlen;
 register unsigned int rectype;
 register struct pktap_record *rp;
 register int (*func)(netdissect_options *, register struct pktap_header *, register u_char *);
 int ret;

 if (caplen < sizeof(struct pktap_header) || length < sizeof(struct pktap_header)) {
  (*ndo->ndo_printf)(ndo, "[|pktap]");
  return(0);
 }

 rp = (struct pktap_record *)cp;
 int dlt = ((rp->pr_dlt & 0xff000000) << 24 | (rp->pr_dlt & 0x00ff0000) << 8 | (rp->pr_dlt & 0x0000ff00) >> 8 | (rp->pr_dlt & 0x000000ff) >> 0);

 hdrlen = ((rp->pr_hdrlen & 0xff000000) << 24 | (rp->pr_hdrlen & 0x00ff0000) << 8 | (rp->pr_hdrlen & 0x0000ff00) >> 8 | (rp->pr_hdrlen & 0x000000ff) >> 0);
 if (hdrlen < sizeof(struct pktap_record)) {
  (*ndo->ndo_printf)(ndo, "[|pktap]");
  return(0);
 }
 if (caplen < hdrlen || length < hdrlen) {
  (*ndo->ndo_printf)(ndo, "[|pktap]");
  ret = hdrlen;
  goto out;
 }

 if (ndo->ndo_vflag)
  pktap_header_print(ndo, cp, length);

 length -= hdrlen;
 caplen -= hdrlen;
 cp += hdrlen;

 rectype = rp->pr_type;
 switch (rectype) {
 case 0:
  (*ndo->ndo_printf)(ndo, "no data");
  break;
 case 1:
  if (--rectype == 0) {
   func = lookup_printer(dlt);
   if (func != NULL) {
    hdrlen += func(ndo, pktaphdr, cp);
    goto done;
   }
   if (!ndo->ndo_vflag)
    pktap_header_print(ndo, (u_char *)rp, hdrlen + length);
   if (!ndo->ndo_qflag)
    (*ndo->ndo_default_print)(ndo, cp, caplen);
  }
  break;
 default:
  break;
 }
 ret = hdrlen;
out:
done:
 return(ret);
}