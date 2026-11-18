__attribute__((used)) static int
lldp_mgmt_addr_print(netdissect_options *ndo,
                     const unsigned char *p, u_int len)
{
    unsigned char addr_len, oid_len, intf_num_subtype;
    unsigned int addr_offset;
    unsigned int oid_offset;
    unsigned int addr_total_len;
    unsigned int intf_num_len;
    unsigned int remaining_len = len;
    char *addr_str;
    const unsigned char *addr_ptr = p;

    if (remaining_len < 2) {
        return 0;
    }

    /* Get the MGMT_ADDR_LEN */
    addr_len = *addr_ptr++;
    remaining_len--;

    /* Check for valid MGMT_ADDR_LEN */
    if (remaining_len < addr_len) {
        return 0;
    }

    /* Get the Network Address */
    addr_str = lldp_network_addr_print(ndo, addr_ptr, addr_len);
    if (addr_str == NULL) {
        return 0;
    }
    (*ndo->ndo_printf)(ndo, "\n\t  Management Address length %u, %s",
                       addr_len, addr_str);

    /* Move the pointer to the start of Interface Numbering */
    addr_ptr += addr_len;
    remaining_len -= addr_len;

    /* Check if there is enough data for Interface Numbering */
    if (remaining_len < 6) {
        return 0;
    }

    /* Get the Interface Number Subtype */
    intf_num_subtype = *addr_ptr++;

    /* Print the Interface Numbering Subtype and Length */
    (*ndo->ndo_printf)(ndo, "\n\t  %s Interface Numbering (%u): %u",
                       tok2str(lldp_intf_numb_subtype_values, "Unknown",
                               intf_num_subtype),
                       ((unsigned int)addr_ptr[0] << 24 | (unsigned int)addr_ptr[1] << 16 |
                        (unsigned int)addr_ptr[2] << 8 | (unsigned int)addr_ptr[3]),
                       ((unsigned int)addr_ptr[0] << 24 | (unsigned int)addr_ptr[1] << 16 |
                        (unsigned int)addr_ptr[2] << 8 | (unsigned int)addr_ptr[3]));

    /* Move the pointer to the start of the Interface Number */
    addr_ptr += 4;
    remaining_len -= 4;

    /* Check if there is enough data for the Interface Number */
    if (remaining_len == 0) {
        return 1;
    }

    /* Get the Interface Number Length */
    intf_num_len = *addr_ptr++;

    /* Check for valid Interface Number Length */
    if (remaining_len < intf_num_len) {
        return 0;
    }

    /* Print the Interface Number */
    if (intf_num_len) {
        (*ndo->ndo_printf)(ndo, "\n\t  Interface Number length %u", intf_num_len);
        safeputs(ndo, (const char *)addr_ptr, intf_num_len);
    }

    /* Move the pointer to the start of the OID */
    addr_ptr += intf_num_len;
    remaining_len -= intf_num_len;

    /* Check if there is enough data for the OID */
    if (remaining_len == 0) {
        return 1;
    }

    /* Get the OID Length */
    oid_len = *addr_ptr++;

    /* Check for valid OID Length */
    if (remaining_len < oid_len) {
        return 0;
    }

    /* Print the OID */
    if (oid_len) {
        (*ndo->ndo_printf)(ndo, "\n\t  OID length %u", oid_len);
        safeputs(ndo, (const char *)addr_ptr, oid_len);
    }

    /* Move the pointer to the start of the next MGMT_ADDR */
    addr_ptr += oid_len;
    remaining_len -= oid_len;

    return 1;
}