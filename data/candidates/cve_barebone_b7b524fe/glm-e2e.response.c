int ospf6_decode_v3(struct ospf6_header *hdr, const void *data, const void *data_end) {
    uint8_t type = *(uint8_t *)((char *)data + 1);
    
    switch (type - 1) {
        case 0: { // HELLO
            const char *cp = (char *)data + 0x10;
            const char *opts = bittok2str(ospf6_option_values, "%#x", EXTRACT_32BITS(cp + 4));
            hdr->printfn(hdr, "\n\tOptions %s", opts);
            
            if (hdr->len - 2 > hdr->len || cp + 0xa > (char *)hdr->len - 2) return 1;
            
            uint16_t iface_id = EXTRACT_16BITS(cp + 8);
            uint16_t prio = EXTRACT_16BITS(cp + 0xa);
            const char *dr = getname(hdr, cp);
            hdr->printfn(hdr, "\n\tHello-ID %d, Priority %d, DR %s", iface_id, prio, dr);
            
            if (hdr->len - 4 > hdr->len || cp + 0xc > (char *)hdr->len - 4) return 1;
            if (EXTRACT_32BITS(cp + 0xc) != 0) {
                const char *bdr = getname(hdr, cp + 0xc);
                hdr->printfn(hdr, ", BDR %s", bdr);
            }
            
            if (hdr->len - 0x10 > hdr->len || cp + 0x10 > (char *)hdr->len - 0x10) return 1;
            if (EXTRACT_32BITS(cp + 0x10) != 0) {
                const char *neighbor = getname(hdr, cp + 0x10);
                hdr->printfn(hdr, "\n\tNeighbor %s", neighbor);
            }
            
            if (hdr->v > 1) {
                hdr->printfn(hdr, "\n\tNeighbors:");
                const char *p = cp + 0x14;
                while (p < data_end) {
                    if (hdr->len - 4 > hdr->len || p > (char *)hdr->len - 4) return 1;
                    const char *n = getname(hdr, p);
                    hdr->printfn(hdr, "\n\t\t%s", n);
                    p += 4;
                }
            }
            break;
        }
        case 1: { // DD
            const char *cp = (char *)data + 0x10;
            if (hdr->len - 4 > hdr->len || cp > (char *)hdr->len - 4) return 1;
            const char *opts = bittok2str(ospf6_option_values, "%#x", EXTRACT_32BITS(cp));
            hdr->printfn(hdr, "\n\tOptions %s", opts);
            
            if (hdr->len - 1 > hdr->len || cp + 7 > (char *)hdr->len - 1) return 1;
            const char *flags = bittok2str(ospf6_dd_flag_values, "%#x", *(uint8_t *)(cp + 7));
            hdr->printfn(hdr, ", Flags %s", flags);
            
            if (hdr->len - 4 > hdr->len || cp + 8 > (char *)hdr->len - 4) return 1;
            uint16_t seq = EXTRACT_16BITS(cp + 4);
            uint32_t mtu = EXTRACT_32BITS(cp + 8);
            hdr->printfn(hdr, ", MTU %u, DD-Sequence 0x%x", mtu, seq);
            
            if (hdr->v > 1) {
                const char *p = cp + 0xc;
                while (p < data_end) {
                    p += 0x14;
                    if (ospf6_print_lshdr(hdr, p, data_end) != 0) return 1;
                }
            }
            break;
        }
        case 2: { // LS_REQ
            if (hdr->v > 1) {
                const char *cp = (char *)data + 0x10;
                while (cp < data_end) {
                    if (hdr->len - 0xc > hdr->len || cp > (char *)hdr->len - 0xc) return 1;
                    const char *adv = getname(hdr, cp + 8);
                    hdr->printfn(hdr, "\n\tAdv-Router %s", adv);
                    uint16_t ls_type = EXTRACT_16BITS(cp + 2);
                    ospf6_print_ls_type(hdr, ls_type, cp + 4);
                    cp += 0xc;
                }
            }
            break;
        }
        case 3: { // LS_UPD
            if (hdr->v > 1) {
                const char *cp = (char *)data + 0x10;
                if (hdr->len - 4 > hdr->len || cp > (char *)hdr->len - 4) return 1;
                uint32_t num_lsa = EXTRACT_32BITS(cp);
                const char *p = cp + 4;
                while (p < data_end && num_lsa-- > 0) {
                    if (ospf6_print_lsa(hdr, p, data_end) != 0) return 1;
                    p += EXTRACT_16BITS(p + 0x12);
                }
            }
            break;
        }
        case 4: { // LS_ACK
            if (hdr->v > 1) {
                const char *cp = (char *)data + 0x10;
                while (cp < data_end) {
                    cp += 0x14;
                    if (ospf6_print_lshdr(hdr, cp, data_end) != 0) return 1;
                }
            }
            break;
        }
        default:
            break;
    }
    
    return 0;
}