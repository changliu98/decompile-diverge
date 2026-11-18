int __cdecl lldp_private_8023_print(netdissect_options *ndo, const u_char *tptr, u_int tlv_len)
{
  int hexdump = 0;
  const char *subtype_str;
  u_int subtype;

  if (tlv_len < 4)
    return 0;

  subtype = tptr[3];
  subtype_str = tok2str(&lldp_8023_subtype_values, "unknown", subtype);
  ndo->ndo_printf(ndo, "\n\t  %s Subtype (%u)", subtype_str, subtype);

  switch (subtype)
  {
    case 1u:
      if (tlv_len >= 9)
      {
        const char *autoneg_str = bittok2str(&lldp_8023_autonegotiation_values, "none", tptr[4]);
        ndo->ndo_printf(ndo, "\n\t    autonegotiation [%s] (0x%02x)", autoneg_str, tptr[4]);

        u_short pmd_cap = _byteswap_ushort(*(u_short *)(tptr + 5));
        const char *pmd_cap_str = bittok2str(&lldp_pmd_capability_values, "unknown", pmd_cap);
        ndo->ndo_printf(ndo, "\n\t    PMD autoneg capability [%s] (0x%04x)", pmd_cap_str, pmd_cap);

        u_short mau_type = _byteswap_ushort(*(u_short *)(tptr + 7));
        const char *mau_type_str = tok2str(&lldp_mau_types_values, "unknown", mau_type);
        ndo->ndo_printf(ndo, "\n\t    MAU type %s (0x%04x)", mau_type_str, mau_type);
      }
      else
      {
        return 0;
      }
      break;

    case 2u:
      if (tlv_len >= 7)
      {
        const char *mdi_str = bittok2str(&lldp_mdi_values, "none", tptr[4]);
        const char *power_pairs_str = tok2str(&lldp_mdi_power_pairs_values, "unknown", tptr[5]);
        const char *power_class_str = tok2str(&lldp_mdi_power_class_values, "unknown", tptr[6]);
        ndo->ndo_printf(ndo, "\n\t    MDI power support [%s], power pair %s, power class %s", mdi_str, power_pairs_str, power_class_str);
      }
      else
      {
        return 0;
      }
      break;

    case 3u:
      if (tlv_len >= 9)
      {
        const char *agg_str = bittok2str(&lldp_aggregation_values, "none", tptr[4]);
        u_int agg_port_id = _byteswap_ulong(*(u_int *)(tptr + 5));
        ndo->ndo_printf(ndo, "\n\t    aggregation status [%s], aggregation port ID %u", agg_str, agg_port_id);
      }
      else
      {
        return 0;
      }
      break;

    case 4u:
      // Fixed pointer arithmetic: originally *((_WORD *)tptr + 2) which evaluates to tptr + 4
      ndo->ndo_printf(ndo, "\n\t    MTU size %u", _byteswap_ushort(*(u_short *)(tptr + 4)));
      break;

    default:
      hexdump = 1;
      break;
  }

  return hexdump;
}