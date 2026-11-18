void eap_print(netdissect_options *ndo,u_char *cp,u_int length)

{
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  byte *pbVar5;
  int len;
  int count;
  u_int subtype;
  u_int type;
  u_int tlen;
  u_char *tptr;
  eap_frame_t *eap;
  u_int length_local;
  u_char *cp_local;
  netdissect_options *ndo_local;
  
  if ((ndo->ndo_snapend < ndo->ndo_snapend + -4) || (ndo->ndo_snapend + -4 < cp)) {
LAB_00101d59:
    (*ndo->ndo_printf)(ndo,"\n\t[|EAP]");
    return;
  }
  if (ndo->ndo_vflag < 1) {
    p_Var1 = ndo->ndo_printf;
    pcVar4 = tok2str(eap_frame_type_values,"unknown",(uint)cp[1]);
    (*p_Var1)(ndo,"%s (%u) v%u, len %u",pcVar4,(ulong)cp[1],(ulong)*cp,(ulong)CONCAT11(cp[2],cp[3]))
    ;
    return;
  }
  p_Var1 = ndo->ndo_printf;
  pcVar4 = tok2str(eap_frame_type_values,"unknown",(uint)cp[1]);
  (*p_Var1)(ndo,"%s (%u) v%u, len %u",pcVar4,(ulong)cp[1],(ulong)*cp,
            (ulong)(((uint)*(ushort *)(cp + 2) | (*(ushort *)(cp + 2) & 0xff) << 0x10) >> 8));
  pbVar5 = cp + 4;
  if (cp[1] != '\0') {
    return;
  }
  uVar2 = (uint)*pbVar5;
  uVar3 = (uint)CONCAT11(cp[6],cp[7]);
  p_Var1 = ndo->ndo_printf;
  pcVar4 = tok2str(eap_code_values,"unknown",uVar2);
  (*p_Var1)(ndo,", %s (%u), id %u, len %u",pcVar4,(ulong)uVar2,(ulong)cp[5],(ulong)uVar3);
  if ((ndo->ndo_snapend < ndo->ndo_snapend + -(long)(int)uVar3) ||
     (ndo->ndo_snapend + -(long)(int)uVar3 < pbVar5)) goto LAB_00101d59;
  if (2 < uVar2) {
    return;
  }
  uVar2 = (uint)cp[8];
  p_Var1 = ndo->ndo_printf;
  pcVar4 = tok2str(eap_type_values,"unknown",(uint)cp[8]);
  (*p_Var1)(ndo,"\n\t\t Type %s (%u)",pcVar4,(ulong)cp[8]);
  if (uVar2 == 1) {
    if ((int)(uVar3 - 5) < 1) {
      return;
    }
    (*ndo->ndo_printf)(ndo,", Identity: ");
    safeputs(ndo,cp + 9,uVar3 - 5);
    return;
  }
  if (uVar2 == 2) {
    if ((int)(uVar3 - 5) < 1) {
      return;
    }
    (*ndo->ndo_printf)(ndo,", Notification: ");
    safeputs(ndo,cp + 9,uVar3 - 5);
    return;
  }
  if (uVar2 == 3) {
    for (count = 5; count < (int)uVar3; count = count + 1) {
      p_Var1 = ndo->ndo_printf;
      pcVar4 = tok2str(eap_type_values,"unknown",(uint)pbVar5[count]);
      (*p_Var1)(ndo," %s (%u),",pcVar4,(ulong)pbVar5[count]);
    }
    return;
  }
  if (uVar2 - 4 < 3) {
    return;
  }
  if (uVar2 == 0xd) {
LAB_00101b33:
    p_Var1 = ndo->ndo_printf;
    pcVar4 = bittok2str(eap_tls_flags_values,"none",(uint)cp[9]);
    (*p_Var1)(ndo," flags [%s] 0x%02x,",pcVar4,(ulong)cp[9]);
    if ((int)(cp[9] & 0x80) >> 7 != 0) {
      (*ndo->ndo_printf)(ndo," len %u",
                         (ulong)((uint)cp[10] << 0x18 | (uint)cp[0xb] << 0x10 | (uint)cp[0xc] << 8 |
                                (uint)cp[0xd]));
    }
  }
  else {
    if (uVar2 != 0x12) {
      if (uVar2 == 0x15) {
        (*ndo->ndo_printf)(ndo," TTLSv%u",(ulong)(cp[9] & 7));
        goto LAB_00101b33;
      }
      if (uVar2 != 0x17) {
        if (uVar2 != 0x2b) {
          return;
        }
        (*ndo->ndo_printf)(ndo," FASTv%u",(ulong)(cp[9] & 7));
        p_Var1 = ndo->ndo_printf;
        pcVar4 = bittok2str(eap_tls_flags_values,"none",(uint)cp[9]);
        (*p_Var1)(ndo," flags [%s] 0x%02x,",pcVar4,(ulong)cp[9]);
        if ((int)(cp[9] & 0x80) >> 7 == 0) {
          return;
        }
        (*ndo->ndo_printf)(ndo," len %u",
                           (ulong)((uint)cp[10] << 0x18 | (uint)cp[0xb] << 0x10 | (uint)cp[0xc] << 8
                                  | (uint)cp[0xd]));
        return;
      }
    }
    p_Var1 = ndo->ndo_printf;
    pcVar4 = tok2str(eap_aka_subtype_values,"unknown",(uint)cp[9]);
    (*p_Var1)(ndo," subtype [%s] 0x%02x,",pcVar4,(ulong)cp[9]);
  }
  return;
}