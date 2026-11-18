int lldp_private_8023_print(struct netdissect_options *ndo, unsigned char *tlv, unsigned int tlv_len)
{
    int ret; int hexdump = 0;
    unsigned int subtype;
    if (tlv_len < 4)
        return 0;
    subtype = tlv[3];
    ndo->ndo_printf(ndo, "\n\t  %s Subtype (%u)",
                    lldp_8023_subtype_valstr(lldp_8023_subtype_values, "unknown", subtype),
                    subtype);
    switch (subtype) {
    case 1:
        if (tlv_len < 4 + 1 + 1 + 2 + 2)
            goto print_hexdump;
        ndo->ndo_printf(ndo, "\n\t    autonegotiation [%s] (0x%02x)",
                        lldp_8023_autonegotiation_valstr(lldp_8023_autonegotiation_values, "none", tlv[4]),
                        tlv[4]);
        ndo->ndo_printf(ndo, "\n\t    PMD autoneg capability [%s] (0x%04x)",
                        lldp_pmd_capability_valstr(lldp_pmd_capability_values, "unknown", (unsigned short)((tlv[5] << 8) | tlv[4 + 1])),
                        (unsigned short)((tlv[5] << 8) | tlv[4 + 1]));
        ndo->ndo_printf(ndo, "\n\t    MAU type %s (0x%04x)",
                        lldp_mau_types_valstr(lldp_mau_types_values, "unknown", (unsigned short)((tlv[7] << 8) | tlv[4 + 1 + 1])),
                        (unsigned short)((tlv[7] << 8) | tlv[4 + 1 + 1]));
    print_hexdump:
        hexdump = 1;
        break;
    case 2:
        if (tlv_len < 4 + 1 + 1 + 1)
            goto print_hexdump;
        ndo->ndo_printf(ndo, "\n\t    MDI power support [%s], power pair %s, power class %s",
                        lldp_mdi_valstr(lldp_mdi_values, "none", tlv[4]),
                        lldp_mdi_power_pairs_valstr(lldp_mdi_power_pairs_values, "unknown", tlv[5]),
                        lldp_mdi_power_class_valstr(lldp_mdi_power_class_values, "unknown", tlv[6]));
        hexdump = 1;
        break;
    case 3:
        if (tlv_len < 4 + 1 + 1 + 2 + 2 + 4)
            goto print_hexdump;
        ndo->ndo_printf(ndo, "\n\t    aggregation status [%s], aggregation port ID %u",
                        lldp_aggregation_valstr(lldp_aggregation_values, "none", tlv[4]),
                        ((unsigned int)(unsigned short)((tlv[5] << 8) | tlv[4 + 1]) << 16) | ((unsigned int)(unsigned short)((tlv[7] << 8) | tlv[4 + 1 + 1]) & 0xFFFF));
        hexdump = 1;
        break;
    case 4:
        ndo->ndo_printf(ndo, "\n\t    MTU size %u",
                        ((unsigned int)(unsigned short)((tlv[1] << 8) | tlv[0]) << 16) | ((unsigned int)(unsigned short)((tlv[3] << 8) | tlv[0 + 1]) & 0xFFFF));
        hexdump = 1;
        break;
    default:
        hexdump = 1;
    }
    ret = hexdump;
    return (ret);
}