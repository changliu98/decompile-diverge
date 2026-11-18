int dhcpv4_print(netdissect_options *ndo,u_char *cp,u_int length,int indent)

{
  byte bVar1;
  byte bVar2;
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var3;
  byte *pbVar4;
  char *pcVar5;
  u_char *tp;
  uint8_t optlen;
  uint8_t type;
  u_char *value;
  u_char *tlv;
  u_int t;
  u_int i;
  int indent_local;
  u_int length_local;
  u_char *cp_local;
  netdissect_options *ndo_local;
  
  i = 0;
  do {
    if (length <= i) {
      return 0;
    }
    pbVar4 = cp + i;
    bVar1 = *pbVar4;
    bVar2 = pbVar4[1];
    pbVar4 = pbVar4 + 2;
    (*ndo->ndo_printf)(ndo,"\n");
    for (t = indent; t != 0; t = t - 1) {
      (*ndo->ndo_printf)(ndo,"\t");
    }
    p_Var3 = ndo->ndo_printf;
    pcVar5 = tok2str(dh4opt_str,"Unknown",(uint)bVar1);
    (*p_Var3)(ndo,"%s",pcVar5);
    (*ndo->ndo_printf)(ndo," (%u)",(ulong)(bVar2 + 2));
    if ((bVar1 == 6) || (bVar1 == 0x2a)) {
      if ((bVar2 < 4) || ((uint)bVar2 % 4 != 0)) {
        return -1;
      }
      for (t = 0; t < bVar2; t = t + 4) {
        p_Var3 = ndo->ndo_printf;
        pcVar5 = getname(ndo,pbVar4 + t);
        (*p_Var3)(ndo," %s",pcVar5);
      }
    }
    else {
      tp = pbVar4;
      if (bVar1 == 0x77) {
        while (tp < pbVar4 + (int)(uint)bVar2) {
          (*ndo->ndo_printf)(ndo," ");
          tp = ns_nprint(ndo,tp,pbVar4 + (int)(uint)bVar2);
          if (tp == (u_char *)0x0) {
            return -1;
          }
        }
      }
    }
    i = bVar2 + 2 + i;
  } while( true );
}