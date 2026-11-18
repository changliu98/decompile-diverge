static int ospf6_decode_v3(netdissect_options *ndo,
                           const struct ospf6_v3_hdr *v3, const u_char *ep) {
  const struct ospf6_v3_options *v3o;
  const struct ospf6_v3_lsa *v3l;
  const struct ospf6_v3_lsr *v3r;
  const struct ospf6_v3_lsu *v3u;
  const struct ospf6_lsa *lsa;
  const struct ospf6_v3_lsu *v3ul;
  const struct ospf6_v3_lsa_sum *v3s;
  const struct ospf6_v3_lsa_sum_lsu *v3sl;
  const u_char *p;
  int i;
  switch (v3->type) {
    case 1:
      ndo->print(ndo, "\n\tOptions [%s]",
                 bittok2str(ospf6_v3_options, "none", EXTRACT_32BITS(&v3->opts)));
      if (ndo->ndo_snapend - 2 > ndo->ndo_snapend ||
          ndo->ndo_snapend - 2 < &v3->mtu)
        return 1;
      ndo->print(ndo,
                 "\n\t  Hello Timer %us, Dead Timer %us, Interface-ID %s, "
                 "Priority %u",
                 EXTRACT_16BITS(&v3->mtu), EXTRACT_16BITS(&v3->ddseq),
                 getname(ndo, &v3->ifid), v3->ddflags);
      if (ndo->ndo_snapend - 4 > ndo->ndo_snapend ||
          ndo->ndo_snapend - 4 < &v3->drid)
        return 1;
      if (EXTRACT_32BITS(&v3->drid))
        ndo->print(ndo, "\n\t  Designated Router %s", getname(ndo, &v3->drid));
      if (ndo->ndo_snapend - 4 > ndo->ndo_snapend ||
          ndo->ndo_snapend - 4 < &v3->bdr)
        return 1;
      if (EXTRACT_32BITS(&v3->bdr))
        ndo->print(ndo, ", Backup Designated Router %s",
                   getname(ndo, &v3->bdr));
      if (ndo->ndo_vflag < 2) return 0;
      ndo->print(ndo, "\n\t  Neighbor List:");
      p = (const u_char *)&v3->neigh;
      while (p < ep) {
        if (ndo->ndo_snapend - 4 > ndo->ndo_snapend || ndo->ndo_snapend - 4 < p)
          return 1;
        ndo->print(ndo, "\n\t    %s", getname(ndo, p));
        p += 4;
      }
      return 0;
    case 2:
      v3o = (const struct ospf6_v3_options *)&v3->lsu;
      if (ndo->ndo_snapend - 4 > ndo->ndo_snapend ||
          ndo->ndo_snapend - 4 < v3o)
        return 1;
      ndo->print(ndo, "\n\tOptions [%s]",
                 bittok2str(ospf6_v3_options, "none", EXTRACT_32BITS(v3o)));
      if (ndo->ndo_snapend - 1 > ndo->ndo_snapend ||
          ndo->ndo_snapend - 1 < &v3->ddflags)
        return 1;
      ndo->print(ndo, ", DD Flags [%s]",
                 bittok2str(ospf6_v3_ddflags, "none", v3->ddflags));
      if (ndo->ndo_snapend - 4 > ndo->ndo_snapend ||
          ndo->ndo_snapend - 4 < &v3->mtu)
        return 1;
      ndo->print(ndo, ", MTU %u, DD-Sequence 0x%08x", v3->mtu,
                 EXTRACT_32BITS(&v3->ddseq));
      if (ndo->ndo_vflag < 2) return 0;
      v3l = (const struct ospf6_v3_lsa *)&v3->lsa;
      while (v3l < (const struct ospf6_v3_lsa *)ep) {
        if (ospf6_print_lshdr(ndo, v3l, ep)) return 1;
        v3l++;
      }
      return 0;
    case 3:
      if (ndo->ndo_vflag < 2) return 0;
      v3r = (const struct ospf6_v3_lsr *)&v3->lsr;
      while (v3r < (const struct ospf6_v3_lsr *)ep) {
        if (ndo->ndo_snapend - 12 > ndo->ndo_snapend ||
            ndo->ndo_snapend - 12 < v3r)
          return 1;
        ndo->print(ndo, "\n\t  Advertising Router %s",
                   getname(ndo, &v3r->arid));
        ospf6_print_ls_type(ndo, EXTRACT_16BITS(&v3r->ls_type),
                            &v3r->ls_mask);
        v3r++;
      }
      return 0;
    case 4:
      if (ndo->ndo_vflag < 2) return 0;
      v3u = (const struct ospf6_v3_lsu *)&v3->lsu;
      if (ndo->ndo_snapend - 4 > ndo->ndo_snapend ||
          ndo->ndo_snapend - 4 < v3u)
        return 1;
      i = EXTRACT_32BITS(v3u);
      lsa = (const struct ospf6_lsa *)&v3->lsa;
      while (lsa < (const struct ospf6_lsa *)ep && i--) {
        if (ospf6_print_lsa(ndo, lsa, ep)) return 1;
        lsa = (const struct ospf6_lsa *)((const u_char *)lsa +
                                         EXTRACT_16BITS(&lsa->lsahdr.lsa_len));
      }
      return 0;
    case 5:
      if (ndo->ndo_vflag < 2) return 0;
      v3ul = (const struct ospf6_v3_lsu *)&v3->lsu;
      while (v3ul < (const struct ospf6_v3_lsu *)ep) {
        if (ospf6_print_lshdr(ndo, v3ul, ep)) return 1;
        v3ul++;
      }
      return 0;
    default:
      return 0;
  }
}