int mp_dss_print(struct netdissect_options *ndo, const uint8_t *cp, uint32_t len, uint8_t flags) {
    const struct dss_hdr *dss = (const struct dss_hdr *)cp;
    int ret = 0;

    // Check if length matches expected DSS length for either flag=1 or flag=0
    if (len != mp_dss_len(dss, 1)) {
        if (len != mp_dss_len(dss, 0) || (flags & 0x2)) {
            return 0;
        }
    }

    // Check if the 'A' (Ack) flag is set (0x10)
    if (dss->flags & 0x10) {
        ndo->printf_func(ndo, " ack");
    }

    cp += 4; // Skip DSS header

    // Check if the 'a' (Ack present) flag is set (0x01)
    if (dss->flags & 0x01) {
        ndo->printf_func(ndo, " ");
        
        // Check if the 'L' (64-bit Ack) flag is set (0x02)
        if (dss->flags & 0x02) {
            uint64_t ack = EXTRACT_64BITS(cp);
            ndo->printf_func(ndo, "ack %" PRIu64, ack);
            cp += 8;
        } else {
            uint32_t ack = EXTRACT_32BITS(cp);
            ndo->printf_func(ndo, "ack %u", ack);
            cp += 4;
        }
    }

    // Check if the 'M' (Map/Data present) flag is set (0x04)
    if (dss->flags & 0x04) {
        ndo->printf_func(ndo, " ");
        
        // Check if the 'm' (64-bit Map) flag is set (0x08)
        if (dss->flags & 0x08) {
            uint64_t dsn = EXTRACT_64BITS(cp);
            ndo->printf_func(ndo, "dsn %" PRIu64, dsn);
            cp += 8;
        } else {
            uint32_t dsn = EXTRACT_32BITS(cp);
            ndo->printf_func(ndo, "dsn %u", dsn);
            cp += 4;
        }

        uint32_t ssn = EXTRACT_32BITS(cp);
        ndo->printf_func(ndo, " subseq %u", ssn);
        cp += 4;

        uint16_t dl = EXTRACT_16BITS(cp);
        ndo->printf_func(ndo, " dl %u", dl);
        cp += 2;

        // If length matches the expected length for flag=1, extract checksum
        if (len == mp_dss_len(dss, 1)) {
            uint16_t cksum = EXTRACT_16BITS(cp);
            ndo->printf_func(ndo, " cksum 0x%x", cksum);
            cp += 2;
        }
    }

    return 1;
}