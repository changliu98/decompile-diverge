struct enamemem *lookup_bytestring(struct netdissect_options *ndo, unsigned char *nsap, unsigned int nlen)
{
  struct enamemem *ep;
  unsigned int addr0; unsigned int addr1; unsigned int addr2;
  if (nlen >= 6) {
    addr0 = (nsap[0] << 8) | nsap[1];
    addr1 = (nsap[2] << 8) | nsap[3];
    addr2 = (nsap[4] << 8) | nsap[5];
  } else if (nlen >= 4) {
    addr0 = 0;
    addr1 = (nsap[0] << 8) | nsap[1];
    addr2 = (nsap[2] << 8) | nsap[3];
  } else {
    addr0 = addr1 = addr2 = 0;
  }
  ep = &bytestringtable[((addr1 ^ addr2) & (sizeof(bytestringtable) - 1))];
  for ( ; ep->e_nxt != ((void *)0); ep = ep->e_nxt) {
    if (ep->e_addr0 == addr0 && ep->e_addr1 == addr1 &&
        ep->e_addr2 == addr2 &&
        memcmp(nsap, ep->e_nsap, nlen) == 0)
      return (ep);
  }
  ep->e_addr0 = addr0;
  ep->e_addr1 = addr1;
  ep->e_addr2 = addr2;
  if ((ep->e_nsap = (unsigned char *) calloc(1, nlen + 1)) == ((void *)0))
    ndo->ndo_error(ndo, "lookup_bytestring: calloc");
  memcpy(ep->e_nsap, nsap, nlen);
  if ((ep->e_nxt = (struct enamemem *) calloc(1, sizeof(struct enamemem))) == ((void *)0))
    ndo->ndo_error(ndo, "lookup_bytestring: calloc");
  return (ep);
}