int isis_print_extd_ip_reach(netdissect_options *ndo,uint8_t *tptr,char *ident,uint16_t afi)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var5;
  uint uVar6;
  int iVar7;
  byte *pbVar8;
  char *pcVar9;
  char *pcVar10;
  undefined *puVar11;
  u_int subtlvlen;
  u_int subtlvtype;
  u_int processed;
  u_int sublen;
  u_int byte_length;
  u_int bit_length;
  u_int status_byte;
  u_int metric;
  uint8_t prefix [16];
  char ident_buffer [20];
  uint16_t afi_local;
  char *ident_local;
  uint8_t *tptr_local;
  netdissect_options *ndo_local;
  u_int local_c;
  
  if ((ndo->ndo_snapend < ndo->ndo_snapend + -4) || (ndo->ndo_snapend + -4 < tptr)) {
    return 0;
  }
  bVar1 = *tptr;
  bVar2 = tptr[1];
  bVar3 = tptr[2];
  bVar4 = tptr[3];
  pbVar8 = tptr + 4;
  if (afi == 2) {
    if ((ndo->ndo_snapend < ndo->ndo_snapend + -1) || (ndo->ndo_snapend + -1 < pbVar8)) {
      return 0;
    }
    tptr_local = tptr + 5;
    status_byte = (u_int)*pbVar8;
    bit_length = status_byte & 0x3f;
    if (0x20 < bit_length) {
      (*ndo->ndo_printf)(ndo,"%sIPv4 prefix: bad bit length %u",ident,(ulong)bit_length);
      return 0;
    }
    processed = 5;
  }
  else {
    if (afi != 10) {
      return 0;
    }
    if ((ndo->ndo_snapend < ndo->ndo_snapend + -1) || (ndo->ndo_snapend + -1 < pbVar8)) {
      return 0;
    }
    status_byte = (u_int)*pbVar8;
    tptr_local = tptr + 6;
    bit_length = (u_int)tptr[5];
    if (0x80 < bit_length) {
      (*ndo->ndo_printf)(ndo,"%sIPv6 prefix: bad bit length %u",ident,(ulong)bit_length);
      return 0;
    }
    processed = 6;
  }
  uVar6 = bit_length + 7 >> 3;
  if ((ndo->ndo_snapend < ndo->ndo_snapend + -(ulong)uVar6) ||
     (ndo->ndo_snapend + -(ulong)uVar6 < tptr_local)) {
    local_c = 0;
  }
  else {
    memset(prefix,0,0x10);
    memcpy(prefix,tptr_local,(ulong)uVar6);
    pbVar8 = tptr_local + uVar6;
    processed = uVar6 + processed;
    if (afi == 2) {
      p_Var5 = ndo->ndo_printf;
      pcVar9 = ipaddr_string(ndo,prefix);
      (*p_Var5)(ndo,"%sIPv4 prefix: %15s/%u",ident,pcVar9,(ulong)bit_length);
    }
    else if (afi == 10) {
      p_Var5 = ndo->ndo_printf;
      pcVar9 = ip6addr_string(ndo,prefix);
      (*p_Var5)(ndo,"%sIPv6 prefix: %s/%u",ident,pcVar9,(ulong)bit_length);
    }
    puVar11 = &DAT_001020f9;
    if ((status_byte & 0x80) != 0) {
      puVar11 = &DAT_001020f4;
    }
    (*ndo->ndo_printf)(ndo,", Distribution: %s, Metric: %u",puVar11,
                       (ulong)((uint)bVar1 << 0x18 | (uint)bVar2 << 0x10 | (uint)bVar3 << 8 |
                              (uint)bVar4));
    if ((afi == 2) && ((status_byte & 0x40) != 0)) {
      (*ndo->ndo_printf)(ndo,", sub-TLVs present");
    }
    else if (afi == 10) {
      pcVar9 = "Internal";
      if ((status_byte & 0x40) != 0) {
        pcVar9 = "External";
      }
      pcVar10 = "";
      if ((status_byte & 0x20) != 0) {
        pcVar10 = ", sub-TLVs present";
      }
      (*ndo->ndo_printf)(ndo,", %s%s",pcVar9,pcVar10);
    }
    if (((afi == 2) && ((status_byte & 0x40) != 0)) || ((afi == 10 && ((status_byte & 0x20) != 0))))
    {
      if ((ndo->ndo_snapend < ndo->ndo_snapend + -1) || (ndo->ndo_snapend + -1 < pbVar8)) {
        return 0;
      }
      tptr_local = pbVar8 + 1;
      sublen = (u_int)*pbVar8;
      processed = sublen + 1 + processed;
      (*ndo->ndo_printf)(ndo," (%u)",(ulong)sublen);
      for (; sublen != 0; sublen = sublen - (uVar6 + 2)) {
        if ((ndo->ndo_snapend < ndo->ndo_snapend + -2) || (ndo->ndo_snapend + -2 < tptr_local)) {
          return 0;
        }
        bVar1 = *tptr_local;
        uVar6 = (uint)tptr_local[1];
        snprintf(ident_buffer,0x14,"%s  ",ident);
        iVar7 = isis_print_ip_reach_subtlv(ndo,tptr_local + 2,(uint)bVar1,uVar6,ident_buffer);
        if (iVar7 == 0) {
          return 0;
        }
        tptr_local = tptr_local + 2 + uVar6;
      }
    }
    local_c = processed;
  }
  return local_c;
}