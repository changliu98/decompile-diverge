int __cdecl ospf6_print_lshdr(netdissect_options *ndo, const lsa6_hdr *lshp, const u_char *dataend)
{
  uint16_t v3; // ax
  uint16_t v4; // ax
  const char *v6; // [rsp+10h] [rbp-40h]
  uint32_t v7; // [rsp+18h] [rbp-38h]
  unsigned int v8; // [rsp+1Ch] [rbp-34h]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+20h] [rbp-30h]

  if ( &lshp[1] > (const lsa6_hdr *)dataend
    || ndo->ndo_snapend - 2 > ndo->ndo_snapend
    || (const u_char *)&lshp->ls_type > ndo->ndo_snapend - 2
    || ndo->ndo_snapend - 4 > ndo->ndo_snapend
    || (const u_char *)&lshp->ls_seq > ndo->ndo_snapend - 4 )
  {
    return 1;
  }
  ndo_printf = ndo->ndo_printf;
  v6 = ipaddr_string(ndo, &lshp->ls_router);
  v7 = EXTRACT_32BITS(&lshp->ls_seq);
  v8 = EXTRACT_16BITS(lshp);
  v3 = EXTRACT_16BITS(&lshp->ls_length);
  ndo_printf(ndo, "\n\t  Advertising Router %s, seq 0x%08x, age %us, length %u", v6, v7, v8, (unsigned int)v3 - 20);
  v4 = EXTRACT_16BITS(&lshp->ls_type);
  ospf6_print_ls_type(ndo, v4, &lshp->ls_stateid);
  return 0;
}