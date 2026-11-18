void ip_optprint(netdissect_options *ndo,u_char *cp,u_int length)

{
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var1;
  uint v;
  char *pcVar2;
  u_int option_code;
  char *sep;
  u_int option_len;
  u_int length_local;
  u_char *cp_local;
  netdissect_options *ndo_local;
  
  sep = "";
  length_local = length;
  cp_local = cp;
  do {
    if (length_local == 0) {
      return;
    }
    (*ndo->ndo_printf)(ndo,"%s",sep);
    sep = ",";
    if ((ndo->ndo_snapend < ndo->ndo_snapend + -1) || (ndo->ndo_snapend + -1 < cp_local)) {
LAB_0010190d:
      (*ndo->ndo_printf)(ndo,"%s","[|ip]");
      return;
    }
    v = (uint)*cp_local;
    p_Var1 = ndo->ndo_printf;
    pcVar2 = tok2str(ip_option_values,"unknown %u",v);
    (*p_Var1)(ndo,"%s",pcVar2);
    if ((v == 1) || (v == 0)) {
      option_len = 1;
    }
    else {
      if ((ndo->ndo_snapend < ndo->ndo_snapend + -1) || (ndo->ndo_snapend + -1 < cp_local + 1))
      goto LAB_0010190d;
      option_len = (u_int)cp_local[1];
      if (option_len < 2) {
        (*ndo->ndo_printf)(ndo," [bad length %u]",(ulong)option_len);
        return;
      }
    }
    if (length_local < option_len) {
      (*ndo->ndo_printf)(ndo," [bad length %u]",(ulong)option_len);
      return;
    }
    if ((ndo->ndo_snapend < ndo->ndo_snapend + -(ulong)option_len) ||
       (ndo->ndo_snapend + -(ulong)option_len < cp_local)) goto LAB_0010190d;
    if (v == 0) {
      return;
    }
    if (v != 1) {
      if (v == 7) {
LAB_001017f5:
        ip_printroute(ndo,cp_local,option_len);
      }
      else if (v == 0x44) {
        ip_printts(ndo,cp_local,option_len);
      }
      else if (v != 0x82) {
        if ((v == 0x83) || (v == 0x89)) goto LAB_001017f5;
        if (v == 0x94) {
          if (option_len < 4) {
            (*ndo->ndo_printf)(ndo," [bad length %u]",(ulong)option_len);
          }
          else {
            if ((ndo->ndo_snapend < ndo->ndo_snapend + -1) || (ndo->ndo_snapend + -1 < cp_local + 3)
               ) goto LAB_0010190d;
            if (CONCAT11(cp_local[2],cp_local[3]) != 0) {
              (*ndo->ndo_printf)(ndo," value %u",(ulong)CONCAT11(cp_local[2],cp_local[3]));
            }
          }
        }
      }
    }
    cp_local = cp_local + option_len;
    length_local = length_local - option_len;
  } while( true );
}