static int
isis_print_extd_ip_reach(struct netdissect_options *ndo,
                   register const u_char *tptr, char *ident, unsigned short afi)
{
    struct in_addr addr;
    unsigned int metric, bitlen, byte_len, status, sublen, subtlvtype, subtlvlen;
    unsigned int total_subtlv_len, total_tlv_len;
    int ret;

    if (tptr + 4 > ndo->ndo_snapend || tptr + 4 > ndo->ndo_snapend) {
        return(0);
    }

    metric = tptr[0] << 24 | tptr[1] << 16 | tptr[2] << 8 | tptr[3];
    total_tlv_len = 4;
    tptr += 4;

    if (afi == 2) {
        if (tptr + 1 > ndo->ndo_snapend || tptr + 1 > ndo->ndo_snapend) {
            return(0);
        }
        status = *tptr++;
        bitlen = status & 0x3f;
        if (bitlen > 32) {
            (*ndo->ndo_error)(ndo, "%sIPv4 prefix: bad bit length %u",
                              ident, bitlen);
            return(0);
        }
        total_tlv_len++;
    } else if (afi == 10) {
        if (tptr + 1 > ndo->ndo_snapend || tptr + 1 > ndo->ndo_snapend) {
            return(0);
        }
        status = *tptr++;
        bitlen = *tptr++;
        if (bitlen > 128) {
            (*ndo->ndo_error)(ndo, "%sIPv6 prefix: bad bit length %u",
                              ident, bitlen);
            return(0);
        }
        total_tlv_len += 2;
    } else {
        return(0);
    }

    byte_len = (bitlen + 7) / 8;
    if ((byte_len > 0 && byte_len > ndo->ndo_snapend - tptr) ||
        (byte_len == 0 && ndo->ndo_snapend - tptr < byte_len)) {
        return(0);
    }
    memset(&addr, 0, sizeof(addr));
    memcpy(&addr, tptr, byte_len);
    tptr += byte_len;
    total_tlv_len += byte_len;

    if (afi == 2) {
        (*ndo->ndo_printf)(ndo, "%sIPv4 prefix: %15s/%u", ident, ipaddr_string(ndo, &addr), bitlen);
    } else if (afi == 10) {
        (*ndo->ndo_printf)(ndo, "%sIPv6 prefix: %s/%u", ident, ip6addr_string(ndo, &addr), bitlen);
    }

    (*ndo->ndo_printf)(ndo, ", Distribution: %s, Metric: %u",
                       (status & 0x80) ? "down" : "up", metric);

    if ((afi == 2 && (status & 0x40)) || (afi == 10 && (status & 0x20))) {
        (*ndo->ndo_printf)(ndo, ", sub-TLVs present");
    }

    if ((afi == 2 && (status & 0x40)) || (afi == 10 && (status & 0x20))) {
        if (tptr + 1 > ndo->ndo_snapend || tptr + 1 > ndo->ndo_snapend) {
            return(0);
        }
        sublen = *tptr++;
        total_tlv_len += sublen + 1;
        (*ndo->ndo_printf)(ndo, " (%u)", sublen);

        while (sublen > 0) {
            if (tptr + 2 > ndo->ndo_snapend || tptr + 2 > ndo->ndo_snapend) {
                return(0);
            }
            subtlvtype = *tptr++;
            subtlvlen = *tptr++;

            char ident_buffer[20];
            snprintf(ident_buffer, sizeof(ident_buffer), "%s  ", ident);

            ret = isis_print_ip_reach_subtlv(ndo, tptr, subtlvtype, subtlvlen, ident_buffer);
            if (!ret) {
                return(0);
            }

            tptr += subtlvlen;
            sublen -= subtlvlen + 2;
        }
    }

    return(total_tlv_len);
}