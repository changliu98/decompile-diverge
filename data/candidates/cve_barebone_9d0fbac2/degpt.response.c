void handle_ppp(netdissect_options *ndo,u_int proto,u_char *p,int length)

{
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var1;
  char *pcVar2;
  int length_local;
  u_char *p_local;
  u_int proto_local;
  netdissect_options *ndo_local;
  
  if ((proto & 0xff00) == 0x7e00) {
    ppp_hdlc(ndo,p + -1,length);
    return;
  }
  if (proto != 0x21) {
    if (proto == 0x23) {
      isoclns_print(ndo,p,length,length);
      return;
    }
    if (proto == 0x2b) {
LAB_00101e31:
      ipx_print(ndo,p,length);
      return;
    }
    if (proto != 0x2f) {
      if (proto == 0x3d) {
        handle_mlppp(ndo,p,length);
        return;
      }
      if (proto == 0x57) {
LAB_00101e1c:
        ip6_print(ndo,p,length);
        return;
      }
      if (proto == 0xfd) {
        (*ndo->ndo_printf)(ndo,"compressed PPP data");
        return;
      }
      if ((proto == 0x281) || (proto == 0x283)) {
        mpls_print(ndo,p,length);
        return;
      }
      if (proto != 0x800) {
        if ((((proto != 0x8021) && (proto != 0x8023)) && (proto != 0x8057)) && (proto != 0x80fd)) {
          if (proto == 0x8137) goto LAB_00101e31;
          if (proto != 0x8281) {
            if (proto == 0x86dd) goto LAB_00101e1c;
            if (proto != 0xc021) {
              if (proto == 0xc023) {
                handle_pap(ndo,p,length);
                return;
              }
              if (proto != 0xc02b) {
                if (proto == 0xc02d) {
                  handle_bap(ndo,p,length);
                  return;
                }
                if (proto != 0xc223) {
                  p_Var1 = ndo->ndo_printf;
                  pcVar2 = tok2str(ppptype2str,"unknown PPP protocol (0x%04x)",proto);
                  (*p_Var1)(ndo,"%s ",pcVar2);
                  print_unknown_data(ndo,p,"\n\t",length);
                  return;
                }
                handle_chap(ndo,p,length);
                return;
              }
            }
          }
        }
        handle_ctrl_proto(ndo,proto,p,length);
        return;
      }
    }
  }
  ip_print(ndo,p,length);
  return;
}