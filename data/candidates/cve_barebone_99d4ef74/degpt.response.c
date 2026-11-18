int lldp_mgmt_addr_tlv_print(netdissect_options *ndo,u_char *pptr,u_int len)

{
  byte bVar1;
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var2;
  uint uVar3;
  char *pcVar4;
  byte *pbVar5;
  char *mgmt_addr;
  u_int tlen;
  u_char *tptr;
  uint8_t oid_len;
  uint8_t intf_num_subtype;
  uint8_t mgmt_addr_len;
  u_int len_local;
  u_char *pptr_local;
  netdissect_options *ndo_local;
  int local_c;
  
  if (len == 0) {
    local_c = 0;
  }
  else {
    bVar1 = *pptr;
    if (len - 1 < (uint)bVar1) {
      local_c = 0;
    }
    else {
      pcVar4 = lldp_network_addr_print(ndo,pptr + 1,(uint)bVar1);
      if (pcVar4 == (char *)0x0) {
        local_c = 0;
      }
      else {
        (*ndo->ndo_printf)(ndo,"\n\t  Management Address length %u, %s",(ulong)bVar1,pcVar4);
        pbVar5 = pptr + 1 + (int)(uint)bVar1;
        uVar3 = (len - 1) - (uint)bVar1;
        if (uVar3 < 5) {
          local_c = 0;
        }
        else {
          bVar1 = *pbVar5;
          p_Var2 = ndo->ndo_printf;
          pcVar4 = tok2str(lldp_intf_numb_subtype_values,"Unknown",(uint)bVar1);
          (*p_Var2)(ndo,"\n\t  %s Interface Numbering (%u): %u",pcVar4,(ulong)bVar1,
                    (ulong)((uint)pbVar5[1] << 0x18 | (uint)pbVar5[2] << 0x10 | (uint)pbVar5[3] << 8
                           | (uint)pbVar5[4]));
          if (uVar3 != 5) {
            bVar1 = pbVar5[5];
            if (uVar3 - 5 < (uint)bVar1) {
              return 0;
            }
            if (bVar1 != 0) {
              (*ndo->ndo_printf)(ndo,"\n\t  OID length %u",(ulong)bVar1);
              safeputs(ndo,pbVar5 + 6,(uint)bVar1);
            }
          }
          local_c = 1;
        }
      }
    }
  }
  return local_c;
}