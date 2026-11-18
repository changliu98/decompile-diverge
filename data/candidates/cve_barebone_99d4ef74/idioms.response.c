int lldp_mgmt_addr_tlv_print(struct netdissect_options *ndo, unsigned char *start, unsigned int length)
{
    unsigned char *end; unsigned char *ptr;
    unsigned int len;
    unsigned char mgmt_addr_len;
    char *mgmt_addr;
    unsigned char intf_num_subtype;
    unsigned char oid_len;
    if (length < 1)
        return 0;
    ptr = start + 1;
    mgmt_addr_len = *start;
    len = length - 1;
    if (len < mgmt_addr_len)
        return 0;
    if ((mgmt_addr = lldp_ntoa(ndo, ptr, mgmt_addr_len)) == ((void *)0))
        return 0;
    ndo->ndo_printf(ndo, "\n\t  Management Address length %u, %s",
                    mgmt_addr_len, mgmt_addr);
    ptr += mgmt_addr_len;
    len -= mgmt_addr_len;
    if (len < 5)
        return 0;
    intf_num_subtype = *ptr;
    ndo->ndo_printf(ndo, "\n\t  %s Interface Numbering (%u): %u",
                    lldp_intf_numb_subtype_valstr(lldp_intf_numb_subtype_values,
                                                  "Unknown", intf_num_subtype),
                    intf_num_subtype,
                    ((unsigned int)ptr[1]) << 24 |
                    ((unsigned int)ptr[2]) << 16 |
                    ((unsigned int)ptr[3]) << 8 |
                    ((unsigned int)ptr[4]));
    ptr += 5;
    len -= 5;
    if (len > 0) {
        oid_len = *ptr;
        if (len < oid_len)
            return 0;
        if (oid_len > 0) {
            ndo->ndo_printf(ndo, "\n\t  OID length %u", oid_len);
            lldp_oid_print(ndo, ptr + 1, oid_len);
        }
    }
    return 1;
}