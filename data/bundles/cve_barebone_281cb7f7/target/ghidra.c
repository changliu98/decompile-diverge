int dhcpv6_print(netdissect_options *ndo,u_char *cp,u_int length,int indent)

{
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var1;
  ushort uVar2;
  ushort uVar3;
  u_char *puVar4;
  char *pcVar5;
  u_char *tp;
  uint16_t optlen;
  uint16_t type;
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
    puVar4 = cp + i;
    uVar2 = CONCAT11(*puVar4,puVar4[1]);
    uVar3 = CONCAT11(puVar4[2],puVar4[3]);
    puVar4 = puVar4 + 4;
    (*ndo->ndo_printf)(ndo,"\n");
    for (t = indent; t != 0; t = t - 1) {
      (*ndo->ndo_printf)(ndo,"\t");
    }
    p_Var1 = ndo->ndo_printf;
    pcVar5 = tok2str(dh6opt_str,"Unknown",(uint)uVar2);
    (*p_Var1)(ndo,"%s",pcVar5);
    (*ndo->ndo_printf)(ndo," (%u)",(ulong)(uVar3 + 4));
    if (uVar2 == 0x17) {
LAB_00101680:
      if ((uint)uVar3 % 0x10 != 0) {
        (*ndo->ndo_printf)(ndo," %s"," (invalid)");
        return -1;
      }
      for (t = 0; t < uVar3; t = t + 0x10) {
        p_Var1 = ndo->ndo_printf;
        pcVar5 = getname6(ndo,puVar4 + t);
        (*p_Var1)(ndo," %s",pcVar5);
      }
    }
    else {
      tp = puVar4;
      if (uVar2 == 0x18) {
        while (tp < puVar4 + (int)(uint)uVar3) {
          (*ndo->ndo_printf)(ndo," ");
          tp = ns_nprint(ndo,tp,puVar4 + (int)(uint)uVar3);
          if (tp == (u_char *)0x0) {
            return -1;
          }
        }
      }
      else if (uVar2 == 0x1f) goto LAB_00101680;
    }
    i = uVar3 + 4 + i;
  } while( true );
}