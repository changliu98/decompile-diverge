u_int mfr_print(netdissect_options *ndo,u_char *p,u_int length)

{
  byte bVar1;
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var2;
  byte bVar3;
  ushort uVar4;
  uint32_t uVar5;
  char *pcVar6;
  char *pcVar7;
  timeval *tvp;
  uint8_t *tptr;
  uint8_t ie_len;
  uint8_t ie_type;
  uint16_t sequence_num;
  u_int hdr_len;
  u_int idx;
  u_int tlen;
  u_int length_local;
  u_char *p_local;
  netdissect_options *ndo_local;
  u_int local_c;
  
  if ((ndo->ndo_snapend < ndo->ndo_snapend + -4) || (ndo->ndo_snapend + -4 < p)) {
LAB_00101d0a:
    (*ndo->ndo_printf)(ndo,"[|mfr]");
    local_c = length;
  }
  else if (((*p & 0xe0) == 0xe0) && (p[1] == '\0')) {
    p_Var2 = ndo->ndo_printf;
    pcVar6 = bittok2str(frf_flag_values,"none",*p & 0xe0);
    pcVar7 = tok2str(mfr_ctrl_msg_values,"Unknown Message (0x%02x)",(uint)p[2]);
    (*p_Var2)(ndo,"FRF.16 Control, Flags [%s], %s, length %u",pcVar6,pcVar7,(ulong)length);
    tptr = p + 3;
    tlen = length - 3;
    if (ndo->ndo_vflag == 0) {
      local_c = 3;
    }
    else {
      for (; 2 < tlen; tlen = (tlen - 2) - (uint)bVar3) {
        if ((ndo->ndo_snapend < ndo->ndo_snapend + -2) || (ndo->ndo_snapend + -2 < tptr))
        goto LAB_00101d0a;
        bVar1 = *tptr;
        bVar3 = tptr[1];
        p_Var2 = ndo->ndo_printf;
        pcVar6 = tok2str(mfr_ctrl_ie_values,"Unknown",(uint)bVar1);
        (*p_Var2)(ndo,"\n\tIE %s (%u), length %u: ",pcVar6,(ulong)bVar1,(ulong)bVar3);
        if ((bVar1 == 0) || (bVar3 < 3)) {
          return 3;
        }
        if ((ndo->ndo_snapend < ndo->ndo_snapend + -(ulong)bVar3) ||
           (ndo->ndo_snapend + -(ulong)bVar3 < tptr)) goto LAB_00101d0a;
        tvp = (timeval *)(tptr + 2);
        bVar3 = bVar3 - 2;
        switch(bVar1) {
        case 1:
        case 2:
          for (idx = 0; (idx < bVar3 && idx < 0x32 &&
                        (*(char *)((long)&tvp->tv_sec + (ulong)idx) != '\0')); idx = idx + 1) {
            safeputchar(ndo,*(u_char *)((long)&tvp->tv_sec + (ulong)idx));
          }
          break;
        case 3:
          p_Var2 = ndo->ndo_printf;
          uVar5 = EXTRACT_32BITS(tvp);
          (*p_Var2)(ndo,"0x%08x",(ulong)uVar5);
          break;
        case 5:
          if (bVar3 != 0x10) goto switchD_00101a47_caseD_6;
          ts_print(ndo,tvp);
          break;
        case 6:
        case 7:
switchD_00101a47_caseD_6:
        default:
          if (ndo->ndo_vflag < 2) {
            print_unknown_data(ndo,(u_char *)tvp,"\n\t  ",(uint)bVar3);
          }
        }
        if (1 < ndo->ndo_vflag) {
          print_unknown_data(ndo,(u_char *)tvp,"\n\t  ",(uint)bVar3);
        }
        tptr = (uint8_t *)((long)&tvp->tv_sec + (long)(int)(uint)bVar3);
      }
      local_c = 3;
    }
  }
  else {
    uVar4 = (*p & 0x1e) << 7 | (ushort)p[1];
    if (((*p & 0xe0) == 0xc0) || ((*p & 0xe0) == 0x80)) {
      p_Var2 = ndo->ndo_printf;
      pcVar6 = bittok2str(frf_flag_values,"none",*p & 0xe0);
      (*p_Var2)(ndo,"FRF.16 Frag, seq %u, Flags [%s], ",(ulong)uVar4,pcVar6);
      fr_print(ndo,p + 2,length - 2);
      local_c = 2;
    }
    else {
      p_Var2 = ndo->ndo_printf;
      pcVar6 = bittok2str(frf_flag_values,"none",*p & 0xe0);
      (*p_Var2)(ndo,"FRF.16 Frag, seq %u, Flags [%s]",(ulong)uVar4,pcVar6);
      print_unknown_data(ndo,p,"\n\t",length);
      local_c = 0;
    }
  }
  return local_c;
}