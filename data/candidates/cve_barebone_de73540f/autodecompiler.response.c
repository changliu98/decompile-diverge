__attribute__((used)) static int
lldp_private_8023_print(netdissect_options *ndo,
                const u_char *tlv, u32 tlv_len)
{
    unsigned subtype;
    int hexdump = 0;

    if (tlv_len < 5) {
        ND_PRINT((ndo, "\n\t  802.3 TLV too short (%u)", tlv_len));
        return(hexdump);
    }

    subtype = tlv[3];
    ND_PRINT((ndo, "\n\t  %s Subtype (%u)",
           tok2str(lldp_8023_subtype_values, "unknown", subtype),
           subtype));

    switch (subtype) {
    case 1: /* Power */
        if (tlv_len < 10) {
            hexdump = 1;
            break;
        }
        ND_PRINT((ndo, "\n\t    autonegotiation [%s] (0x%02x)",
               bittok2str(lldp_8023_autonegotiation_values, "none",
                          tlv[4]),
               tlv[4]));
        ND_PRINT((ndo, "\n\t    PMD autoneg capability [%s] (0x%04x)",
               bittok2str(lldp_pmd_capability_values, "unknown",
                          ((tlv[5] << 8) | tlv[6])),
                          tlv[5], tlv[6]),
               ((tlv[5] << 8) | tlv[6])));
        ND_PRINT((ndo, "\n\t    MAU type %s (0x%04x)",
               tok2str(lldp_mau_types_values, "unknown",
                       ((tlv[7] << 8) | tlv[8])),
                       tlv[7], tlv[8]),
               ((tlv[7] << 8) | tlv[8])));
        break;
    case 2: /* MDI */
        if (tlv_len < 8) {
            hexdump = 1;
            break;
        }
        ND_PRINT((ndo, "\n\t    MDI power support [%s], power pairs %s, class %s",
               bittok2str(lldp_mdi_values, "none", tlv[4]),
               tok2str(lldp_mdi_power_pairs_values, "unknown", tlv[5]),
               tok2str(lldp_mdi_power_class_values, "unknown", tlv[6])));
        break;
    case 3: /* Aggregation */
        if (tlv_len < 10) {
            hexdump = 1;
            break;
        }
        ND_PRINT((ndo, "\n\t    aggregation status [%s], aggregator ID %u",
               bittok2str(lldp_aggregation_values, "none", tlv[4]),
               ((tlv[5] << 24) | (tlv[6] << 16) | (tlv[7] << 8) | tlv[8])));
        break;
    case 4: /* MTU */
        if (tlv_len < 6) {
            hexdump = 1;
            break;
        }
        ND_PRINT((ndo, "\n\t    MTU size %u",
               ((tlv[4] << 8) | tlv[5])));
        break;
    default:
        hexdump = 1;
    }

    return(hexdump);
}