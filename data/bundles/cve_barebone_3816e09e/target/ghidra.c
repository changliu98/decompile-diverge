int mobility_opt_print(netdissect_options *ndo,u_char *bp,uint len)

{
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var1;
  uint16_t uVar2;
  uint16_t uVar3;
  char *pcVar4;
  uint optlen;
  uint i;
  uint len_local;
  u_char *bp_local;
  netdissect_options *ndo_local;
  
  i = 0;
  while( true ) {
    if (len <= i) {
      return 0;
    }
    if ((ndo->ndo_snapend < ndo->ndo_snapend + -1) || (ndo->ndo_snapend + -1 < bp + i)) {
      return 1;
    }
    if (bp[i] == '\0') {
      optlen = 1;
    }
    else {
      if (len <= i + 1) {
        return 1;
      }
      if (ndo->ndo_snapend < ndo->ndo_snapend + -1) {
        return 1;
      }
      if (ndo->ndo_snapend + -1 < bp + (i + 1)) {
        return 1;
      }
      optlen = bp[i + 1] + 2;
    }
    if (len < i + optlen) {
      return 1;
    }
    if (ndo->ndo_snapend < ndo->ndo_snapend + -1) break;
    if (ndo->ndo_snapend + -1 < bp + (i + optlen)) {
      return 1;
    }
    switch(bp[i]) {
    case '\0':
      (*ndo->ndo_printf)(ndo,"(pad1)");
      break;
    case '\x01':
      if (len - i < 2) {
        (*ndo->ndo_printf)(ndo,"(padn: trunc)");
        return 1;
      }
      (*ndo->ndo_printf)(ndo,"(padn)");
      break;
    case '\x02':
      if (len - i < 4) {
        (*ndo->ndo_printf)(ndo,"(refresh: trunc)");
        return 1;
      }
      p_Var1 = ndo->ndo_printf;
      uVar2 = EXTRACT_16BITS(bp + (i + 2));
      (*p_Var1)(ndo,"(refresh: %u)",(ulong)uVar2 << 2);
      break;
    case '\x03':
      if (len - i < 0x12) {
        (*ndo->ndo_printf)(ndo,"(altcoa: trunc)");
        return 1;
      }
      p_Var1 = ndo->ndo_printf;
      pcVar4 = getname6(ndo,bp + (i + 2));
      (*p_Var1)(ndo,"(alt-CoA: %s)",pcVar4);
      break;
    case '\x04':
      if (len - i < 6) {
        (*ndo->ndo_printf)(ndo,"(ni: trunc)");
        return 1;
      }
      p_Var1 = ndo->ndo_printf;
      uVar2 = EXTRACT_16BITS(bp + (i + 2));
      uVar3 = EXTRACT_16BITS(bp + (i + 4));
      (*p_Var1)(ndo,"(ni: ho=0x%04x co=0x%04x)",(ulong)uVar2,(ulong)uVar3);
      break;
    case '\x05':
      if (len - i < 0xc) {
        (*ndo->ndo_printf)(ndo,"(auth: trunc)");
        return 1;
      }
      (*ndo->ndo_printf)(ndo,"(auth)");
      break;
    default:
      if (len - i < 2) {
        (*ndo->ndo_printf)(ndo,"(sopt_type %u: trunc)",(ulong)bp[i]);
        return 1;
      }
      (*ndo->ndo_printf)(ndo,"(type-0x%02x: len=%u)",(ulong)bp[i],(ulong)bp[i + 1]);
    }
    i = optlen + i;
  }
  return 1;
}