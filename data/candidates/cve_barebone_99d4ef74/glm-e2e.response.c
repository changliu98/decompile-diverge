int lldp_mgmt_addr_tlv_print(stream_t *stream, const uint8_t *pptr, uint32_t length) {
    const uint8_t *tptr = pptr;
    uint32_t tlen = length;
    uint8_t addr_len;
    uint8_t intf_subtype;
    uint8_t oid_len;

    // Check if there's at least 1 byte for the address length
    if (tlen < 1) {
        return 0;
    }
    
    // Read address length and advance pointer
    addr_len = *tptr;
    tptr++;
    tlen--;

    // Check if remaining length is sufficient for the address
    if (tlen < addr_len) {
        return 0;
    }

    // Print network address
    const char *addr_str = lldp_network_addr_print(stream, tptr, addr_len);
    if (addr_str == NULL) {
        return 0;
    }

    // Print the formatted address string
    stream->printf_func("\n  Management Address length: %u, %s", addr_len, addr_str);

    // Advance pointer past the address
    tptr += addr_len;
    tlen -= addr_len;

    // Check if there's enough length for the interface numbering (5 bytes)
    if (tlen < 5) {
        return 0;
    }

    // Read interface numbering subtype
    intf_subtype = *tptr;

    // Look up the interface subtype string
    const char *intf_str = tok2str(lldp_intf_numb_subtype_values, "Unknown", intf_subtype);

    // Read the 4-byte interface number (Big Endian)
    uint32_t intf_num = ((uint32_t)tptr[1] << 24) |
                        ((uint32_t)tptr[2] << 16) |
                        ((uint32_t)tptr[3] << 8)  |
                        ((uint32_t)tptr[4]);

    // Print interface subtype and number
    stream->printf_func("\n  IfId subtype: %s (%u), IfId: %u", intf_str, intf_subtype, intf_num);

    // Advance pointer past the interface numbering
    tptr += 5;
    tlen -= 5;

    // Process OID if present
    if (tlen != 0) {
        oid_len = *tptr;

        // Check if remaining length is sufficient for the OID
        if (tlen < oid_len) {
            return 0;
        }

        // Print and output OID if length is non-zero
        if (oid_len != 0) {
            stream->printf_func("\n  OID length: %u", oid_len);
            safeputs(stream, tptr + 1, oid_len);
        }
    }

    return 1;
}