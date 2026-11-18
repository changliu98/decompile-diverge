void vrrp_print(struct netdissect_options *ndo, const uint8_t *bp, uint16_t len, const uint8_t *bp2, uint8_t ttl) {
    int version = (bp[0] & 0xF0) >> 4;
    int type = bp[0] & 0x0F;
    const char *type_s = tok2str(type2str, "vrrp-?-%d", type);
    int auth_type = 0;
    int naddr = 0;
    uint16_t cksum = 0;
    char sep = ' ';
    int i;

    ndo->ndo_printf(ndo, "VRRPv%d-type-%d %s", version, type, type_s);
    if (ttl != 255) {
        ndo->ndo_printf(ndo, "[ttl=%d]", ttl);
    }

    if (version < 2 || version > 3 || type != 1) {
        return;
    }

    ndo->ndo_printf(ndo, " vrid=%d prio=%d", bp[1], bp[2]);

    if (version == 2) {
        auth_type = bp[4];
        ndo->ndo_printf(ndo, " authtype=%s", tok2str(auth2str, "0x%x", auth_type));
        ndo->ndo_printf(ndo, " intvl=%d advskew=%d", bp[5], len);
    } else {
        cksum = ((bp[4] & 0x0F) << 8) | bp[5];
        ndo->ndo_printf(ndo, " intvl=%d cksum=0x%04x", len, cksum);
    }

    if (ndo->ndo_vflag) {
        naddr = bp[3];

        if (version == 2) {
            if (len > 0) {
                if (ndo->ndo_snapend - len >= ndo->ndo_snapend || bp >= ndo->ndo_snapend - len) {
                    if (in_cksum(bp, len) != 0) {
                        ndo->ndo_printf(ndo, " (bad vrrp cksum %x)", EXTRACT_16BITS(bp + 6));
                    }
                }
            }
        } else if (version == 3) {
            if (len > 0) {
                if (ndo->ndo_snapend - len >= ndo->ndo_snapend || bp >= ndo->ndo_snapend - len) {
                    if (nextproto4_cksum(ndo, bp, len, len, 0x70) != 0) {
                        ndo->ndo_printf(ndo, " (bad vrrp cksum %x)", EXTRACT_16BITS(bp + 6));
                    }
                }
            }
        }

        ndo->ndo_printf(ndo, " addrs");
        if (naddr > 1) {
            ndo->ndo_printf(ndo, "(%d)", naddr);
        }
        ndo->ndo_printf(ndo, ":");

        bp += 8;
        for (i = 0; i < naddr; i++) {
            ndo->ndo_printf(ndo, "%c%s", sep, getname(ndo, bp));
            sep = ',';
            bp += 4;
        }

        if (version == 2 && auth_type == 1) {
            ndo->ndo_printf(ndo, " auth ");
            if (fn_printn(ndo, bp, 8, NULL)) {
                ndo->ndo_printf(ndo, "[|vrrp]");
                return;
            }
            ndo->ndo_printf(ndo, "[|vrrp]");
        }
    }
}