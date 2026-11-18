int ospf6_decode_v3(netdissect_options *ndo,ospf6hdr *op,u_char *dataend)

{
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var1;
  uint16_t uVar2;
  uint16_t uVar3;
  uint32_t uVar4;
  int iVar5;
  char *pcVar6;
  lsu6 *lsup;
  dd6 *ddp;
  hello6 *hellop;
  int i;
  lsa6 *lsap;
  lsa6_hdr *lshp;
  lsr6 *lsrp;
  rtrid_t *ap;
  u_char *dataend_local;
  ospf6hdr *op_local;
  netdissect_options *ndo_local;
  
  switch(op->ospf6_type) {
  case '\x01':
    p_Var1 = ndo->ndo_printf;
    uVar4 = EXTRACT_32BITS(&op[1].ospf6_routerid);
    pcVar6 = bittok2str(ospf6_option_values,"none",uVar4);
    (*p_Var1)(ndo,"\n\tOptions [%s]",pcVar6);
    if ((ndo->ndo_snapend + -2 <= ndo->ndo_snapend) &&
       ((u_char *)((long)&op[1].ospf6_areaid + 2U) <= ndo->ndo_snapend + -2)) {
      p_Var1 = ndo->ndo_printf;
      uVar3 = EXTRACT_16BITS(&op[1].ospf6_areaid);
      uVar2 = EXTRACT_16BITS((void *)((long)&op[1].ospf6_areaid + 2));
      pcVar6 = getname(ndo,&op[1].ospf6_version);
      (*p_Var1)(ndo,"\n\t  Hello Timer %us, Dead Timer %us, Interface-ID %s, Priority %u",
                (ulong)uVar3,(ulong)uVar2,pcVar6,(ulong)(byte)op[1].ospf6_routerid);
      if ((ndo->ndo_snapend + -4 <= ndo->ndo_snapend) &&
         (&op[1].ospf6_chksum <= ndo->ndo_snapend + -4)) {
        uVar4 = EXTRACT_32BITS(&op[1].ospf6_chksum);
        if (uVar4 != 0) {
          p_Var1 = ndo->ndo_printf;
          pcVar6 = getname(ndo,(u_char *)&op[1].ospf6_chksum);
          (*p_Var1)(ndo,"\n\t  Designated Router %s",pcVar6);
        }
        if ((ndo->ndo_snapend + -4 <= ndo->ndo_snapend) &&
           (op + 2 <= (ospf6hdr *)(ndo->ndo_snapend + -4))) {
          uVar4 = EXTRACT_32BITS(op + 2);
          if (uVar4 != 0) {
            p_Var1 = ndo->ndo_printf;
            pcVar6 = getname(ndo,&op[2].ospf6_version);
            (*p_Var1)(ndo,", Backup Designated Router %s",pcVar6);
          }
          if (ndo->ndo_vflag < 2) {
            return 0;
          }
          (*ndo->ndo_printf)(ndo,"\n\t  Neighbor List:");
          ap = &op[2].ospf6_routerid;
          while( true ) {
            if (dataend <= ap) {
              return 0;
            }
            if (ndo->ndo_snapend < ndo->ndo_snapend + -4) break;
            if (ndo->ndo_snapend + -4 < ap) {
              return 1;
            }
            p_Var1 = ndo->ndo_printf;
            pcVar6 = getname(ndo,(u_char *)ap);
            (*p_Var1)(ndo,"\n\t    %s",pcVar6);
            ap = ap + 1;
          }
          return 1;
        }
      }
    }
    break;
  case '\x02':
    if ((ndo->ndo_snapend + -4 <= ndo->ndo_snapend) &&
       (op + 1 <= (ospf6hdr *)(ndo->ndo_snapend + -4))) {
      p_Var1 = ndo->ndo_printf;
      uVar4 = EXTRACT_32BITS(op + 1);
      pcVar6 = bittok2str(ospf6_option_values,"none",uVar4);
      (*p_Var1)(ndo,"\n\tOptions [%s]",pcVar6);
      if ((ndo->ndo_snapend + -1 <= ndo->ndo_snapend) &&
         ((u_char *)((long)&op[1].ospf6_routerid + 3U) <= ndo->ndo_snapend + -1)) {
        p_Var1 = ndo->ndo_printf;
        pcVar6 = bittok2str(ospf6_dd_flag_values,"none",
                            (uint)*(byte *)((long)&op[1].ospf6_routerid + 3));
        (*p_Var1)(ndo,", DD Flags [%s]",pcVar6);
        if ((ndo->ndo_snapend + -4 <= ndo->ndo_snapend) &&
           (&op[1].ospf6_areaid <= ndo->ndo_snapend + -4)) {
          p_Var1 = ndo->ndo_printf;
          uVar3 = EXTRACT_16BITS(&op[1].ospf6_routerid);
          uVar4 = EXTRACT_32BITS(&op[1].ospf6_areaid);
          (*p_Var1)(ndo,", MTU %u, DD-Sequence 0x%08x",(ulong)uVar3,(ulong)uVar4);
          if (ndo->ndo_vflag < 2) {
            return 0;
          }
          lshp = (lsa6_hdr *)&op[1].ospf6_chksum;
          do {
            if (dataend <= lshp) {
              return 0;
            }
            iVar5 = ospf6_print_lshdr(ndo,lshp,dataend);
            lshp = lshp + 1;
          } while (iVar5 == 0);
        }
      }
    }
    break;
  case '\x03':
    if (ndo->ndo_vflag < 2) {
      return 0;
    }
    lsrp = (lsr6 *)(op + 1);
    while( true ) {
      if (dataend <= lsrp) {
        return 0;
      }
      if (ndo->ndo_snapend < ndo->ndo_snapend + -0xc) break;
      if ((lsr6 *)(ndo->ndo_snapend + -0xc) < lsrp) {
        return 1;
      }
      p_Var1 = ndo->ndo_printf;
      pcVar6 = getname(ndo,(u_char *)&lsrp->ls_router);
      (*p_Var1)(ndo,"\n\t  Advertising Router %s",pcVar6);
      uVar3 = EXTRACT_16BITS(&lsrp->ls_type);
      ospf6_print_ls_type(ndo,(uint)uVar3,&lsrp->ls_stateid);
      lsrp = lsrp + 1;
    }
    return 1;
  case '\x04':
    if (ndo->ndo_vflag < 2) {
      return 0;
    }
    if ((ndo->ndo_snapend + -4 <= ndo->ndo_snapend) &&
       (op + 1 <= (ospf6hdr *)(ndo->ndo_snapend + -4))) {
      i = EXTRACT_32BITS(op + 1);
      lsap = (lsa6 *)&op[1].ospf6_routerid;
      while( true ) {
        iVar5 = i;
        if (lsap < dataend) {
          i = i + -1;
        }
        if (lsap >= dataend || iVar5 == 0) {
          return 0;
        }
        iVar5 = ospf6_print_lsa(ndo,lsap,dataend);
        if (iVar5 != 0) break;
        uVar3 = EXTRACT_16BITS(&(lsap->ls_hdr).ls_length);
        lsap = (lsa6 *)((long)&(lsap->ls_hdr).ls_age + (long)(int)(uint)uVar3);
      }
    }
    break;
  case '\x05':
    if (ndo->ndo_vflag < 2) {
      return 0;
    }
    lshp = (lsa6_hdr *)(op + 1);
    do {
      if (dataend <= lshp) {
        return 0;
      }
      iVar5 = ospf6_print_lshdr(ndo,lshp,dataend);
      lshp = lshp + 1;
    } while (iVar5 == 0);
    break;
  default:
    return 0;
  }
  return 1;
}