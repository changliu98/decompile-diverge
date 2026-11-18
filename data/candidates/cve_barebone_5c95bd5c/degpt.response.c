int rpki_rtr_pdu_print(netdissect_options *ndo,u_char *tptr,u_int indent)

{
  byte bVar1;
  u_char uVar2;
  u_char uVar3;
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var4;
  bool bVar5;
  uint len;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  char *pcVar9;
  u_int error_code;
  u_int tlen;
  u_int text_length;
  u_int encapsulated_pdu_length;
  rpki_rtr_pdu_error_report *pdu_2;
  rpki_rtr_pdu_ipv6_prefix *pdu_1;
  rpki_rtr_pdu_ipv4_prefix *pdu;
  u_char *msg;
  u_int hexdump;
  u_int pdu_len;
  u_int pdu_type;
  rpki_rtr_pdu *pdu_header;
  u_int indent_local;
  u_char *tptr_local;
  netdissect_options *ndo_local;
  int local_c;
  
  uVar6 = (uint)tptr[1];
  len = (uint)tptr[4] << 0x18 | (uint)tptr[5] << 0x10 | (uint)tptr[6] << 8 | (uint)tptr[7];
  if ((ndo->ndo_snapend < ndo->ndo_snapend + -(ulong)len) || (ndo->ndo_snapend + -(ulong)len < tptr)
     ) {
LAB_00101b3e:
    local_c = 1;
  }
  else {
    bVar5 = false;
    p_Var4 = ndo->ndo_printf;
    pcVar8 = indent_string(8);
    bVar1 = *tptr;
    pcVar9 = tok2str(rpki_rtr_pdu_values,"Unknown",uVar6);
    (*p_Var4)(ndo,"%sRPKI-RTRv%u, %s PDU (%u), length: %u",pcVar8,(ulong)bVar1,pcVar9,(ulong)uVar6,
              len);
    tptr_local = tptr;
    switch(uVar6) {
    case 0:
    case 1:
    case 7:
      p_Var4 = ndo->ndo_printf;
      pcVar8 = indent_string(indent + 2);
      (*p_Var4)(ndo,"%sSession ID: 0x%04x, Serial: %u",pcVar8,(ulong)CONCAT11(tptr[2],tptr[3]),
                (ulong)((uint)tptr[8] << 0x18 | (uint)tptr[9] << 0x10 | (uint)tptr[10] << 8 |
                       (uint)tptr[0xb]));
      break;
    case 2:
    case 8:
      break;
    case 3:
      p_Var4 = ndo->ndo_printf;
      pcVar8 = indent_string(indent + 2);
      (*p_Var4)(ndo,"%sSession ID: 0x%04x",pcVar8,(ulong)CONCAT11(tptr[2],tptr[3]));
      break;
    case 4:
      p_Var4 = ndo->ndo_printf;
      pcVar8 = indent_string(indent + 2);
      pcVar9 = getname(ndo,tptr + 0xc);
      (*p_Var4)(ndo,"%sIPv4 Prefix %s/%u-%u, origin-as %u, flags 0x%02x",pcVar8,pcVar9,
                (ulong)tptr[9],(ulong)tptr[10],
                (uint)tptr[0x10] << 0x18 | (uint)tptr[0x11] << 0x10 | (uint)tptr[0x12] << 8 |
                (uint)tptr[0x13],(uint)tptr[8]);
      break;
    default:
      bVar5 = true;
      break;
    case 6:
      p_Var4 = ndo->ndo_printf;
      pcVar8 = indent_string(indent + 2);
      pcVar9 = getname6(ndo,tptr + 0xc);
      (*p_Var4)(ndo,"%sIPv6 Prefix %s/%u-%u, origin-as %u, flags 0x%02x",pcVar8,pcVar9,
                (ulong)tptr[9],(ulong)tptr[10],
                (uint)tptr[0x1c] << 0x18 | (uint)tptr[0x1d] << 0x10 | (uint)tptr[0x1e] << 8 |
                (uint)tptr[0x1f],(uint)tptr[8]);
      break;
    case 10:
      uVar6 = (uint)tptr[8] << 0x18 | (uint)tptr[9] << 0x10 | (uint)tptr[10] << 8 | (uint)tptr[0xb];
      if ((ndo->ndo_snapend + -(ulong)uVar6 <= ndo->ndo_snapend) &&
         (tptr <= ndo->ndo_snapend + -(ulong)uVar6)) {
        uVar2 = tptr[2];
        uVar3 = tptr[3];
        p_Var4 = ndo->ndo_printf;
        pcVar8 = indent_string(indent + 2);
        pcVar9 = tok2str(rpki_rtr_error_codes,"Unknown",(uint)CONCAT11(uVar2,uVar3));
        (*p_Var4)(ndo,"%sError code: %s (%u), Encapsulated PDU length: %u",pcVar8,pcVar9,
                  (ulong)(uint)CONCAT11(uVar2,uVar3),(ulong)uVar6);
        if ((uVar6 != 0) && (uVar6 <= len - 0xc)) {
          p_Var4 = ndo->ndo_printf;
          pcVar8 = indent_string(indent + 4);
          (*p_Var4)(ndo,"%s-----encapsulated PDU-----",pcVar8);
          iVar7 = rpki_rtr_pdu_print(ndo,tptr + 0xc,indent + 2);
          if (iVar7 != 0) goto LAB_00101b3e;
        }
        tptr_local = tptr + 0xc + uVar6;
        tlen = (len - 0xc) - uVar6;
        text_length = 0;
        if (4 < tlen) {
          text_length = (uint)*tptr_local << 0x18 | (uint)tptr_local[1] << 0x10 |
                        (uint)tptr_local[2] << 8 | (uint)tptr_local[3];
          tptr_local = tptr_local + 4;
          tlen = tlen - 4;
        }
        if ((ndo->ndo_snapend + -(ulong)text_length <= ndo->ndo_snapend) &&
           (tptr_local <= ndo->ndo_snapend + -(ulong)text_length)) {
          if ((text_length != 0) && (text_length <= tlen)) {
            p_Var4 = ndo->ndo_printf;
            pcVar8 = indent_string(indent + 2);
            (*p_Var4)(ndo,"%sError text: ",pcVar8);
            iVar7 = fn_printn(ndo,tptr_local,text_length,ndo->ndo_snapend);
            if (iVar7 != 0) goto LAB_00101b3e;
          }
          break;
        }
      }
      goto LAB_00101b3e;
    }
    if ((1 < ndo->ndo_vflag) || ((ndo->ndo_vflag != 0 && (bVar5)))) {
      print_unknown_data(ndo,tptr_local,"\n\t  ",len);
    }
    local_c = 0;
  }
  return local_c;
}