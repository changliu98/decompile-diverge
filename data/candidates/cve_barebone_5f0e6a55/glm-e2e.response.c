int ieee802_15_4_if_print(struct netdissect_options *ndo, const uint8_t *p, uint32_t caplen) {
    uint32_t ret = 3;
    uint16_t panid = 0;
    uint16_t fc;
    uint8_t seq;
    uint32_t dst_mode, src_mode;

    if (caplen < 3) {
        ndo->ndo_printf(ndo, " [|802.15.4]");
        return caplen;
    }

    // Read Frame Control (2 bytes, little-endian)
    fc = (p[1] << 8) | p[0];
    seq = p[2];
    p += 3;
    caplen -= 3;

    // Print Frame Type
    ndo->ndo_printf(ndo, "IEEE 802.15.4 %s packet ", ftypes[fc & 0x7]);

    if (ndo->ndo_print) {
        ndo->ndo_printf(ndo, "seq %02x ", seq);
    }

    dst_mode = (fc >> 10) & 0x3;
    src_mode = (fc >> 14) & 0x3;

    // Parse Destination Addressing
    switch (dst_mode) {
        case 0:
            if (fc & 0x40) { // PAN ID Compression
                ndo->ndo_printf(ndo, " [|802.15.4]");
                return ret;
            }
            if (ndo->ndo_print) {
                ndo->ndo_printf(ndo, "dst not present");
            }
            break;
        case 1:
            if (ndo->ndo_print) {
                ndo->ndo_printf(ndo, "dst res");
            }
            return ret;
        case 2:
            if (caplen < 2) {
                ndo->ndo_printf(ndo, " [|802.15.4]");
                return ret;
            }
            panid = (p[1] << 8) | p[0];
            p += 2;
            caplen -= 2;
            ret += 2;

            if (caplen < 2) {
                ndo->ndo_printf(ndo, " [|802.15.4]");
                return ret;
            }
            if (ndo->ndo_print) {
                uint16_t short_addr = (p[1] << 8) | p[0];
                ndo->ndo_printf(ndo, "dst %04x:%04x ", panid, short_addr);
            }
            p += 2;
            caplen -= 2;
            ret += 2;
            break;
        case 3:
            if (caplen < 2) {
                ndo->ndo_printf(ndo, " [|802.15.4]");
                return ret;
            }
            panid = (p[1] << 8) | p[0];
            p += 2;
            caplen -= 2;
            ret += 2;

            if (caplen < 8) {
                ndo->ndo_printf(ndo, " [|802.15.4]");
                return ret;
            }
            if (ndo->ndo_print) {
                char *dst_str = le64addr_string(ndo, p);
                ndo->ndo_printf(ndo, "dst %s ", dst_str);
            }
            p += 8;
            caplen -= 8;
            ret += 8;
            break;
    }

    if (ndo->ndo_print) {
        ndo->ndo_printf(ndo, "src ");
    }

    // Parse Source Addressing
    switch (src_mode) {
        case 0:
            if (ndo->ndo_print) {
                ndo->ndo_printf(ndo, "not present");
            }
            break;
        case 1:
            if (ndo->ndo_print) {
                ndo->ndo_printf(ndo, "res");
            }
            return 0;
        case 2:
            if (!(fc & 0x40)) { // If PAN ID Compression is NOT set
                if (caplen < 2) {
                    ndo->ndo_printf(ndo, " [|802.15.4]");
                    return ret;
                }
                panid = (p[1] << 8) | p[0];
                p += 2;
                caplen -= 2;
                ret += 2;
            }
            if (caplen < 2) {
                ndo->ndo_printf(ndo, " [|802.15.4]");
                return ret;
            }
            if (ndo->ndo_print) {
                uint16_t short_addr = (p[1] << 8) | p[0];
                ndo->ndo_printf(ndo, "%04x:%04x ", panid, short_addr);
            }
            p += 2;
            caplen -= 2;
            ret += 2;
            break;
        case 3:
            if (!(fc & 0x40)) { // If PAN ID Compression is NOT set
                if (caplen < 2) {
                    ndo->ndo_printf(ndo, " [|802.15.4]");
                    return ret;
                }
                panid = (p[1] << 8) | p[0];
                p += 2;
                caplen -= 2;
                ret += 2;
            }
            if (caplen < 8) {
                ndo->ndo_printf(ndo, " [|802.15.4]");
                return ret;
            }
            if (ndo->ndo_print) {
                char *src_str = le64addr_string(ndo, p);
                ndo->ndo_printf(ndo, "%s ", src_str);
            }
            p += 8;
            caplen -= 8;
            ret += 8;
            break;
    }

    if (!ndo->ndo_pad) {
        ndo->ndo_default_print(ndo, p, caplen);
    }

    return ret;
}