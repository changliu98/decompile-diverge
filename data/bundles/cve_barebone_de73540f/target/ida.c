int __cdecl lldp_private_8023_print(netdissect_options *ndo, const u_char *tptr, u_int tlv_len)
{
  const char *v3; // rax
  char *v4; // rdx
  char *v5; // rax
  const char *v6; // rax
  const char *v7; // rax
  char *v8; // rax
  int (*v10)(netdissect_options *, const char *, ...); // [rsp+8h] [rbp-98h]
  char *v11; // [rsp+18h] [rbp-88h]
  const char *v12; // [rsp+20h] [rbp-80h]
  int (*v13)(netdissect_options *, const char *, ...); // [rsp+28h] [rbp-78h]
  int (*v14)(netdissect_options *, const char *, ...); // [rsp+38h] [rbp-68h]
  int (*v15)(netdissect_options *, const char *, ...); // [rsp+48h] [rbp-58h]
  int (*v16)(netdissect_options *, const char *, ...); // [rsp+58h] [rbp-48h]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+68h] [rbp-38h]
  int hexdump; // [rsp+7Ch] [rbp-24h]
  unsigned int subtype; // [rsp+80h] [rbp-20h]
  int v21; // [rsp+9Ch] [rbp-4h]

  hexdump = 0;
  if ( tlv_len < 4 )
    return 0;
  subtype = tptr[3];
  ndo_printf = ndo->ndo_printf;
  v3 = tok2str(&lldp_8023_subtype_values, "unknown", subtype);
  ndo_printf(ndo, "\n\t  %s Subtype (%u)", v3, subtype);
  switch ( subtype )
  {
    case 1u:
      if ( tlv_len >= 9 )
      {
        v14 = ndo->ndo_printf;
        v4 = bittok2str(&lldp_8023_autonegotiation_values, "none", tptr[4]);
        v14(ndo, "\n\t    autonegotiation [%s] (0x%02x)", v4, tptr[4]);
        v15 = ndo->ndo_printf;
        v5 = bittok2str(&lldp_pmd_capability_values, "unknown", _byteswap_ushort(*(_WORD *)(tptr + 5)));
        v15(ndo, "\n\t    PMD autoneg capability [%s] (0x%04x)", v5, _byteswap_ushort(*(_WORD *)(tptr + 5)));
        v16 = ndo->ndo_printf;
        v6 = tok2str(&lldp_mau_types_values, "unknown", _byteswap_ushort(*(_WORD *)(tptr + 7)));
        v16(ndo, "\n\t    MAU type %s (0x%04x)", v6, _byteswap_ushort(*(_WORD *)(tptr + 7)));
        goto LABEL_15;
      }
      v21 = 0;
      break;
    case 2u:
      if ( tlv_len >= 7 )
      {
        v13 = ndo->ndo_printf;
        v11 = bittok2str(&lldp_mdi_values, "none", tptr[4]);
        v12 = tok2str(&lldp_mdi_power_pairs_values, "unknown", tptr[5]);
        v7 = tok2str(&lldp_mdi_power_class_values, "unknown", tptr[6]);
        v13(ndo, "\n\t    MDI power support [%s], power pair %s, power class %s", v11, v12, v7);
        goto LABEL_15;
      }
      v21 = 0;
      break;
    case 3u:
      if ( tlv_len >= 9 )
      {
        v10 = ndo->ndo_printf;
        v8 = bittok2str(&lldp_aggregation_values, "none", tptr[4]);
        v10(ndo, "\n\t    aggregation status [%s], aggregation port ID %u", v8, _byteswap_ulong(*(_DWORD *)(tptr + 5)));
        goto LABEL_15;
      }
      v21 = 0;
      break;
    case 4u:
      ndo->ndo_printf(ndo, "\n\t    MTU size %u", _byteswap_ushort(*((_WORD *)tptr + 2)));
      goto LABEL_15;
    default:
      hexdump = 1;
LABEL_15:
      v21 = hexdump;
      break;
  }
  return v21;
}