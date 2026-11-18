int lldp_private_8023_print(netdissect_options *ndo,u_char *tptr,u_int tlv_len)

{
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var1;
  uint v;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  int hexdump;
  int subtype;
  u_int tlv_len_local;
  u_char *tptr_local;
  netdissect_options *ndo_local;
  int local_c;
  
  hexdump = 0;
  if (tlv_len < 4) {
    local_c = 0;
  }
  else {
    v = (uint)tptr[3];
    p_Var1 = ndo->ndo_printf;
    pcVar2 = tok2str(lldp_8023_subtype_values,"unknown",v);
    (*p_Var1)(ndo,"\n\t  %s Subtype (%u)",pcVar2,(ulong)v);
    switch(v) {
    case 1:
      if (tlv_len < 9) {
        return 0;
      }
      p_Var1 = ndo->ndo_printf;
      pcVar2 = bittok2str(lldp_8023_autonegotiation_values,"none",(uint)tptr[4]);
      (*p_Var1)(ndo,"\n\t    autonegotiation [%s] (0x%02x)",pcVar2,(ulong)tptr[4]);
      p_Var1 = ndo->ndo_printf;
      pcVar2 = bittok2str(lldp_pmd_capability_values,"unknown",(uint)CONCAT11(tptr[5],tptr[6]));
      (*p_Var1)(ndo,"\n\t    PMD autoneg capability [%s] (0x%04x)",pcVar2,
                (ulong)CONCAT11(tptr[5],tptr[6]));
      p_Var1 = ndo->ndo_printf;
      pcVar2 = tok2str(lldp_mau_types_values,"unknown",(uint)CONCAT11(tptr[7],tptr[8]));
      (*p_Var1)(ndo,"\n\t    MAU type %s (0x%04x)",pcVar2,(ulong)CONCAT11(tptr[7],tptr[8]));
      break;
    case 2:
      if (tlv_len < 7) {
        return 0;
      }
      p_Var1 = ndo->ndo_printf;
      pcVar2 = bittok2str(lldp_mdi_values,"none",(uint)tptr[4]);
      pcVar3 = tok2str(lldp_mdi_power_pairs_values,"unknown",(uint)tptr[5]);
      pcVar4 = tok2str(lldp_mdi_power_class_values,"unknown",(uint)tptr[6]);
      (*p_Var1)(ndo,"\n\t    MDI power support [%s], power pair %s, power class %s",pcVar2,pcVar3,
                pcVar4);
      break;
    case 3:
      if (tlv_len < 9) {
        return 0;
      }
      p_Var1 = ndo->ndo_printf;
      pcVar2 = bittok2str(lldp_aggregation_values,"none",(uint)tptr[4]);
      (*p_Var1)(ndo,"\n\t    aggregation status [%s], aggregation port ID %u",pcVar2,
                (ulong)((uint)tptr[5] << 0x18 | (uint)tptr[6] << 0x10 | (uint)tptr[7] << 8 |
                       (uint)tptr[8]));
      break;
    case 4:
      (*ndo->ndo_printf)(ndo,"\n\t    MTU size %u",(ulong)CONCAT11(tptr[4],tptr[5]));
      break;
    default:
      hexdump = 1;
    }
    local_c = hexdump;
  }
  return local_c;
}