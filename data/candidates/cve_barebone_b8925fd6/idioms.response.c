int ospf6_print_lshdr(struct netdissect_options *ndo, struct lsa6_hdr *lsap, unsigned char *end)
{
  int (*ndo_printf)(struct netdissect_options *, char *, ...);
  struct in6_addr *addr;
  unsigned int seqno;
  unsigned int age;
  if (lsap->ls_router.ip6.u6_addr32[0] > (unsigned int)(end - sizeof(struct lsa6_hdr))
      || (ndo->ndo_snapend - sizeof(unsigned short)) > ndo->ndo_snapend
      || (ndo->ndo_snapend - (lsap->ls_type)) > ndo->ndo_snapend - sizeof(unsigned short)
      || (ndo->ndo_snapend - (lsap->ls_length)) > ndo->ndo_snapend - sizeof(unsigned short)
      || (ndo->ndo_snapend - (lsap->ls_seq)) > ndo->ndo_snapend - sizeof(unsigned int))
    return 1;
  ndo_printf = ndo->ndo_printf;
  addr = (struct in6_addr *)&lsap->ls_router;
  ndo_printf("\n\t  Advertising Router %s",
      rpl_print_ip6addr(ndo, addr));
  seqno = rpl_getseqno(&lsap->ls_seq);
  age = rpl_getage(&lsap->ls_seq);
  ndo_printf(", seq 0x%08x, age %us", seqno, age);
  ndo_printf(", length %u", rpl_get16uint(&lsap->ls_length) - sizeof(struct lsa6_hdr));
  ndo_printf(", type %s", rpl_print_lsatype(ndo, rpl_get16uint(&lsap->ls_type), &lsap->ls_stateid));
  return 0;
}