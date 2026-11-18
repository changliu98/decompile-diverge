static int lldp_private_8023_print(netdissect_options *ndo,
                                   const unsigned char *p, unsigned length) {
  unsigned subtype;
  int hflag = 0;
  if (length < 4) return 0;
  subtype = p[3];
  ndo->ndo_hexdump_line(ndo, "\n\t  %s Subtype (%u)",
                        tok2str(lldp_private_8023_subtype_values, "unknown",
                                subtype),
                        subtype);
  switch (subtype) {
    case 1:
      if (length < 9) return 0;
      ndo->ndo_hexdump_line(ndo, "\n\t    autonegotiation [%s] (0x%02x)",
                            bittok2str(lldp_private_8023_autoneg_values, "none",
                                       p[4]),
                            p[4]);
      ndo->ndo_hexdump_line(ndo, "\n\t    PMD autoneg capability [%s] (0x%04x)",
                            bittok2str(lldp_private_8023_autoneg_cap_values,
                                       "unknown", (p[5] << 8) | p[6]),
                            (p[5] << 8) | p[6]);
      ndo->ndo_hexdump_line(ndo, "\n\t    MAU type %s (0x%04x)",
                            tok2str(lldp_private_8023_mau_type_values, "unknown",
                                    (p[7] << 8) | p[8]),
                            (p[7] << 8) | p[8]);
      break;
    case 2:
      if (length < 7) return 0;
      ndo->ndo_hexdump_line(ndo,
                            "\n\t    MDI power support [%s], power pair %s, power class %s",
                            bittok2str(lldp_private_8023_mdi_power_values, "none",
                                       p[4]),
                            tok2str(lldp_private_8023_mdi_power_pair_values,
                                    "unknown", p[5]),
                            tok2str(lldp_private_8023_mdi_power_class_values,
                                    "unknown", p[6]));
      break;
    case 3:
      if (length < 9) return 0;
      ndo->ndo_hexdump_line(ndo,
                            "\n\t    aggregation status [%s], aggregation port ID %u",
                            bittok2str(lldp_private_8023_aggregation_values,
                                       "none", p[4]),
                            (p[5] << 24) | (p[6] << 16) | (p[7] << 8) | p[8]);
      break;
    case 4:
      ndo->ndo_hexdump_line(ndo, "\n\t    MTU size %u",
                            (p[2] << 8) | p[1]);
      break;
    default:
      hflag = 1;
      break;
  }
  return hflag;
}