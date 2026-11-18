int mp_dss_print(netdissect_options *ndo,u_char *opt,u_int opt_len,u_char flags)

{
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var1;
  uint16_t uVar2;
  u_int uVar3;
  uint32_t uVar4;
  uint64_t uVar5;
  mp_dss *mdss;
  u_char flags_local;
  u_int opt_len_local;
  u_char *opt_local;
  netdissect_options *ndo_local;
  int local_c;
  
  uVar3 = mp_dss_len((mp_dss *)opt,1);
  if (((opt_len == uVar3) || (uVar3 = mp_dss_len((mp_dss *)opt,0), opt_len == uVar3)) &&
     ((flags & 2) == 0)) {
    if ((opt[3] & 0x10) != 0) {
      (*ndo->ndo_printf)(ndo," fin");
    }
    opt_local = opt + 4;
    if ((opt[3] & 1) != 0) {
      (*ndo->ndo_printf)(ndo," ack ");
      if ((opt[3] & 2) == 0) {
        p_Var1 = ndo->ndo_printf;
        uVar4 = EXTRACT_32BITS(opt_local);
        (*p_Var1)(ndo,"%u",(ulong)uVar4);
        opt_local = opt + 8;
      }
      else {
        p_Var1 = ndo->ndo_printf;
        uVar5 = EXTRACT_64BITS(opt_local);
        (*p_Var1)(ndo,"%lu",uVar5);
        opt_local = opt + 0xc;
      }
    }
    if ((opt[3] & 4) != 0) {
      (*ndo->ndo_printf)(ndo," seq ");
      if ((opt[3] & 8) == 0) {
        p_Var1 = ndo->ndo_printf;
        uVar4 = EXTRACT_32BITS(opt_local);
        (*p_Var1)(ndo,"%u",(ulong)uVar4);
        opt_local = opt_local + 4;
      }
      else {
        p_Var1 = ndo->ndo_printf;
        uVar5 = EXTRACT_64BITS(opt_local);
        (*p_Var1)(ndo,"%lu",uVar5);
        opt_local = opt_local + 8;
      }
      p_Var1 = ndo->ndo_printf;
      uVar4 = EXTRACT_32BITS(opt_local);
      (*p_Var1)(ndo," subseq %u",(ulong)uVar4);
      p_Var1 = ndo->ndo_printf;
      uVar2 = EXTRACT_16BITS(opt_local + 4);
      (*p_Var1)(ndo," len %u",(ulong)uVar2);
      uVar3 = mp_dss_len((mp_dss *)opt,1);
      if (opt_len == uVar3) {
        p_Var1 = ndo->ndo_printf;
        uVar2 = EXTRACT_16BITS(opt_local + 6);
        (*p_Var1)(ndo," csum 0x%x",(ulong)uVar2);
      }
    }
    local_c = 1;
  }
  else {
    local_c = 0;
  }
  return local_c;
}