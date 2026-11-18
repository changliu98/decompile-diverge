void handle_mlppp(netdissect_options *ndo,u_char *p,int length)

{
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var1;
  uint16_t uVar2;
  char *pcVar3;
  int length_local;
  u_char *p_local;
  netdissect_options *ndo_local;
  
  if (ndo->ndo_eflag == 0) {
    (*ndo->ndo_printf)(ndo,"MLPPP, ");
  }
  p_Var1 = ndo->ndo_printf;
  uVar2 = EXTRACT_16BITS(p);
  pcVar3 = bittok2str(ppp_ml_flag_values,"none",*p & 0xc0);
  (*p_Var1)(ndo,"seq 0x%03x, Flags [%s], length %u",(ulong)(uVar2 & 0xfff),pcVar3,
            (ulong)(uint)length);
  return;
}