void vqp_print(netdissect_options *ndo,u_char *pptr,u_int len)

{
  byte bVar1;
  byte bVar2;
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var3;
  uint16_t uVar4;
  uint32_t uVar5;
  char *pcVar6;
  char *pcVar7;
  u_char *cp;
  uint8_t nitems;
  int tlen;
  uint32_t vqp_obj_type;
  uint16_t vqp_obj_len;
  u_char *tptr;
  vqp_obj_tlv_t *vqp_obj_tlv;
  vqp_common_header_t *vqp_common_header;
  u_int len_local;
  u_char *pptr_local;
  netdissect_options *ndo_local;
  
  if ((ndo->ndo_snapend < ndo->ndo_snapend + -8) || (ndo->ndo_snapend + -8 < pptr)) {
LAB_001018dc:
    (*ndo->ndo_printf)(ndo,"\n\t[|VQP]");
  }
  else if (*pptr == '\x01') {
    if (ndo->ndo_vflag < 1) {
      p_Var3 = ndo->ndo_printf;
      bVar1 = *pptr;
      pcVar6 = tok2str(vqp_msg_type_values,"unknown (%u)",(uint)pptr[1]);
      pcVar7 = tok2str(vqp_error_code_values,"unknown (%u)",(uint)pptr[2]);
      (*p_Var3)(ndo,"VQPv%u %s Message, error-code %s (%u), length %u",(ulong)bVar1,pcVar6,pcVar7,
                (ulong)pptr[2],len);
    }
    else {
      nitems = pptr[3];
      p_Var3 = ndo->ndo_printf;
      bVar1 = *pptr;
      pcVar6 = tok2str(vqp_msg_type_values,"unknown (%u)",(uint)pptr[1]);
      pcVar7 = tok2str(vqp_error_code_values,"unknown (%u)",(uint)pptr[2]);
      bVar2 = pptr[2];
      uVar5 = EXTRACT_32BITS(pptr + 4);
      (*p_Var3)(ndo,"\n\tVQPv%u, %s Message, error-code %s (%u), seq 0x%08x, items %u, length %u",
                (ulong)bVar1,pcVar6,pcVar7,(ulong)bVar2,uVar5,(uint)nitems,len);
      tptr = pptr + 8;
      tlen = len - 8;
      for (; nitems != '\0' && 0 < tlen; nitems = nitems + 0xff) {
        uVar5 = EXTRACT_32BITS(tptr);
        uVar4 = EXTRACT_16BITS(tptr + 4);
        cp = tptr + 6;
        p_Var3 = ndo->ndo_printf;
        pcVar6 = tok2str(vqp_obj_values,"Unknown",uVar5);
        (*p_Var3)(ndo,"\n\t  %s Object (0x%08x), length %u, value: ",pcVar6,(ulong)uVar5,
                  (ulong)uVar4);
        if (uVar5 == 0) {
          return;
        }
        if (uVar4 == 0) {
          return;
        }
        if ((ndo->ndo_snapend < ndo->ndo_snapend + -(ulong)uVar4) ||
           (ndo->ndo_snapend + -(ulong)uVar4 < cp)) goto LAB_001018dc;
        switch(uVar5) {
        case 0xc01:
          p_Var3 = ndo->ndo_printf;
          pcVar6 = ipaddr_string(ndo,cp);
          uVar5 = EXTRACT_32BITS(cp);
          (*p_Var3)(ndo,"%s (0x%08x)",pcVar6,(ulong)uVar5);
          break;
        case 0xc02:
        case 0xc03:
        case 0xc04:
        case 0xc05:
          safeputs(ndo,cp,(uint)uVar4);
          break;
        case 0xc06:
        case 0xc08:
          p_Var3 = ndo->ndo_printf;
          pcVar6 = etheraddr_string(ndo,cp);
          (*p_Var3)(ndo,"%s",pcVar6);
          break;
        default:
          if (ndo->ndo_vflag < 2) {
            print_unknown_data(ndo,cp,"\n\t    ",(uint)uVar4);
          }
        }
        tptr = cp + (int)(uint)uVar4;
        tlen = (tlen + -6) - (uint)uVar4;
      }
    }
  }
  else {
    (*ndo->ndo_printf)(ndo,"VQP version %u packet not supported",(ulong)*pptr);
  }
  return;
}