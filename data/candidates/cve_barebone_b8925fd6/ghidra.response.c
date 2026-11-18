int ospf6_print_lshdr(netdissect_options *ndo,lsa6_hdr *lshp,u_char *dataend)

{
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var1;
  uint16_t uVar2;
  uint16_t uVar3;
  uint32_t uVar4;
  char *pcVar5;
  u_char *dataend_local;
  lsa6_hdr *lshp_local;
  netdissect_options *ndo_local;
  int local_c;
  
  if ((((dataend < lshp + 1) || (ndo->ndo_snapend < ndo->ndo_snapend + -2)) ||
      (ndo->ndo_snapend + -2 < &lshp->ls_type)) ||
     ((ndo->ndo_snapend < ndo->ndo_snapend + -4 || (ndo->ndo_snapend + -4 < &lshp->ls_seq)))) {
    local_c = 1;
  }
  else {
    p_Var1 = ndo->ndo_printf;
    pcVar5 = ipaddr_string(ndo,&lshp->ls_router);
    uVar4 = EXTRACT_32BITS(&lshp->ls_seq);
    uVar2 = EXTRACT_16BITS(lshp);
    uVar3 = EXTRACT_16BITS(&lshp->ls_length);
    (*p_Var1)(ndo,"\n\t  Advertising Router %s, seq 0x%08x, age %us, length %u",pcVar5,(ulong)uVar4,
              (ulong)uVar2,(ulong)(uVar3 - 0x14));
    uVar2 = EXTRACT_16BITS(&lshp->ls_type);
    ospf6_print_ls_type(ndo,(uint)uVar2,&lshp->ls_stateid);
    local_c = 0;
  }
  return local_c;
}