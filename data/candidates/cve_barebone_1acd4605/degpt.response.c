u_int chdlc_print(netdissect_options *ndo,u_char *p,u_int length)

{
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var1;
  uint16_t uVar2;
  uint v;
  u_int length_00;
  char *pcVar3;
  char *pcVar4;
  u_char *bp;
  u_int proto;
  u_int length_local;
  u_char *p_local;
  netdissect_options *ndo_local;
  
  uVar2 = EXTRACT_16BITS(p + 2);
  v = (uint)uVar2;
  if (ndo->ndo_eflag != 0) {
    p_Var1 = ndo->ndo_printf;
    pcVar3 = tok2str(chdlc_cast_values,"0x%02x",(uint)*p);
    pcVar4 = tok2str(ethertype_values,"Unknown",v);
    (*p_Var1)(ndo,"%s, ethertype %s (0x%04x), length %u: ",pcVar3,pcVar4,(ulong)v,(ulong)length);
  }
  length_00 = length - 4;
  bp = p + 4;
  if (v == 0x800) {
    ip_print(ndo,bp,length_00);
  }
  else if (v == 0x8035) {
    chdlc_slarp_print(ndo,bp,length_00);
  }
  else if (v == 0x86dd) {
    ip6_print(ndo,bp,length_00);
  }
  else if (v - 0x8847 < 2) {
    mpls_print(ndo,bp,length_00);
  }
  else if (v == 0xfefe) {
    if (((p[5] == 0x81) || (p[5] == 0x82)) || (p[5] == 0x83)) {
      isoclns_print(ndo,p + 5,length - 5,((int)ndo->ndo_snapend - (int)bp) - 1);
    }
    else {
      isoclns_print(ndo,bp,length_00,(int)ndo->ndo_snapend - (int)bp);
    }
  }
  else if (ndo->ndo_eflag == 0) {
    (*ndo->ndo_printf)(ndo,"unknown CHDLC protocol (0x%04x)",(ulong)v);
  }
  return 4;
}