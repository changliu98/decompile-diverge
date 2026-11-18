int __cdecl lldp_mgmt_addr_tlv_print(netdissect_options *ndo, const u_char *pptr, u_int len)
{
    const u_char *tptr;
    u_int tlen;
    uint8_t mgmt_addr_len;
    const char *mgmt_addr;

    // 1. Validate initial length and extract Management Address Length
    if (len == 0)
        return 0;

    mgmt_addr_len = *pptr;
    tptr = pptr + 1;
    tlen = len - 1;

    if (tlen < mgmt_addr_len)
        return 0;

    // 2. Print Management Address
    mgmt_addr = lldp_network_addr_print(ndo, tptr, mgmt_addr_len);
    if (!mgmt_addr)
        return 0;

    ndo->ndo_printf(ndo, "\n\t  Management Address length %u, %s", mgmt_addr_len, mgmt_addr);

    // Advance pointer past the management address
    tptr += mgmt_addr_len;
    tlen -= mgmt_addr_len;

    // 3. Validate and print Interface Numbering
    if (tlen < 5)
        return 0;

    uint8_t intf_num_subtype = *tptr;
    const char *subtype_str = tok2str(&lldp_intf_numb_subtype_values, "Unknown", intf_num_subtype);
    
    // Read 4-byte interface number (big-endian) and swap to host order
    uint32_t intf_num = _byteswap_ulong(*(uint32_t *)(tptr + 1));
    
    ndo->ndo_printf(ndo, "\n\t  %s Interface Numbering (%u): %u", subtype_str, intf_num_subtype, intf_num);

    // Advance pointer past the interface numbering subtype (1 byte) and value (4 bytes)
    tptr += 5;
    tlen -= 5;

    // 4. Validate and print OID (Object Identifier)
    if (tlen == 0)
        return 1;

    uint8_t oid_len = *tptr;
    if (tlen < oid_len)
        return 0;

    if (oid_len > 0)
    {
        ndo->ndo_printf(ndo, "\n\t  OID length %u", oid_len);
        safeputs(ndo, tptr + 1, oid_len);
    }

    return 1;
}