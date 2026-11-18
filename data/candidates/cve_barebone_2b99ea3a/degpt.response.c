int frag6_print(netdissect_options *ndo,u_char *bp,u_char *bp2)

{
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var1;
  uint16_t uVar2;
  uint16_t uVar3;
  uint32_t uVar4;
  ip6_hdr *ip6;
  ip6_frag *dp;
  u_char *bp2_local;
  u_char *bp_local;
  netdissect_options *ndo_local;
  int local_c;
  
  if ((ndo->ndo_snapend < ndo->ndo_snapend + -2) || (ndo->ndo_snapend + -2 < bp + 2)) {
    (*ndo->ndo_printf)(ndo,"[|frag]");
    local_c = -1;
  }
  else {
    if (ndo->ndo_vflag == 0) {
      p_Var1 = ndo->ndo_printf;
      uVar2 = EXTRACT_16BITS(bp + 2);
      uVar3 = EXTRACT_16BITS(bp2 + 4);
      (*p_Var1)(ndo,"frag (%d|%ld)",(ulong)(uVar2 & 0xfff8),
                ((ulong)uVar3 - ((long)bp - (long)bp2)) + 0x20);
    }
    else {
      p_Var1 = ndo->ndo_printf;
      uVar4 = EXTRACT_32BITS(bp + 4);
      uVar2 = EXTRACT_16BITS(bp + 2);
      uVar3 = EXTRACT_16BITS(bp2 + 4);
      (*p_Var1)(ndo,"frag (0x%08x:%d|%ld)",(ulong)uVar4,(ulong)(uVar2 & 0xfff8),
                ((ulong)uVar3 - ((long)bp - (long)bp2)) + 0x20);
    }
    uVar2 = EXTRACT_16BITS(bp + 2);
    if ((uVar2 & 0xfff8) == 0) {
      (*ndo->ndo_printf)(ndo," ");
      local_c = 8;
    }
    else {
      local_c = -1;
    }
  }
  return local_c;
}