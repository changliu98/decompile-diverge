void isoclns_print(netdissect_options *ndo,uint8_t *p,u_int length,u_int caplen)

{
  uint8_t uVar1;
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var2;
  int iVar3;
  char *pcVar4;
  undefined *puVar5;
  u_int caplen_local;
  u_int length_local;
  uint8_t *p_local;
  netdissect_options *ndo_local;
  
  if (caplen < 2) {
    (*ndo->ndo_printf)(ndo,"|OSI");
  }
  else {
    if (ndo->ndo_eflag != 0) {
      p_Var2 = ndo->ndo_printf;
      pcVar4 = tok2str(nlpid_values,"Unknown",(uint)*p);
      (*p_Var2)(ndo,"OSI NLPID %s (0x%02x): ",pcVar4,(ulong)*p);
    }
    uVar1 = *p;
    if (uVar1 == '\0') {
      puVar5 = &DAT_00102039;
      if (ndo->ndo_eflag != 0) {
        puVar5 = &DAT_0010202b;
      }
      (*ndo->ndo_printf)(ndo,"%slength: %u",puVar5,(ulong)length);
    }
    else if (uVar1 == '\b') {
      q933_print(ndo,p + 1,length - 1);
    }
    else if (uVar1 == 0x81) {
      iVar3 = clnp_print(ndo,p,length);
      if (iVar3 == 0) {
        print_unknown_data(ndo,p,"\n\t",caplen);
      }
    }
    else if (uVar1 == 0x82) {
      esis_print(ndo,p,length);
    }
    else if (uVar1 == 0x83) {
      iVar3 = isis_print(ndo,p,length);
      if (iVar3 == 0) {
        print_unknown_data(ndo,p,"\n\t",caplen);
      }
    }
    else if (uVar1 == 0x8e) {
      ip6_print(ndo,p + 1,length - 1);
    }
    else if (uVar1 == 0xcc) {
      ip_print(ndo,p + 1,length - 1);
    }
    else if (uVar1 == 0xcf) {
      ppp_print(ndo,p + 1,length - 1);
    }
    else {
      if (ndo->ndo_eflag == 0) {
        (*ndo->ndo_printf)(ndo,"OSI NLPID 0x%02x unknown",(ulong)*p);
      }
      puVar5 = &DAT_00102039;
      if (ndo->ndo_eflag != 0) {
        puVar5 = &DAT_0010202b;
      }
      (*ndo->ndo_printf)(ndo,"%slength: %u",puVar5,(ulong)length);
      if (1 < caplen) {
        print_unknown_data(ndo,p,"\n\t",caplen);
      }
    }
  }
  return;
}