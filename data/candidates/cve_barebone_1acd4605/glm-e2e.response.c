int chdlc_print(struct netdissect_options *ndo, const uint8_t *p, uint32_t length) {
    uint16_t proto = EXTRACT_16BITS(p + 2);

    if (ndo->ndo_eflag != 0) {
        void (*printfn)(struct netdissect_options *, const char *, ...) = ndo->ndo_printfn;
        const char *cast_str = tok2str(chdlc_cast_values, "unknown", *p);
        const char *proto_str = tok2str(ethertype_values, "unknown CHDLC protocol (0x%04x)", proto);
        
        printfn(ndo, "CHDLC, %s, length %u: %s", cast_str, proto, length, proto_str);
    }

    length -= 4;
    p += 4;

    switch (proto) {
        case 0x800:
            ip_print(ndo, p, length);
            break;
        case 0x86dd:
            ip6_print(ndo, p, length);
            break;
        case 0x8035:
            chdlc_slarp_print(ndo, p, length);
            break;
        case 0x8847:
        case 0x8848:
            mpls_print(ndo, p, length);
            break;
        case 0xfefe:
            if (p[1] == 0x81 || p[1] == 0x82 || p[1] == 0x83) {
                isoclns_print(ndo, p + 1, length - 1, ndo->ndo_snapend - p - 1);
            } else {
                isoclns_print(ndo, p, length, ndo->ndo_snapend - p);
            }
            break;
        default:
            if (ndo->ndo_eflag == 0) {
                ndo->ndo_default_print(ndo, p, length);
            }
            break;
    }

    return 4;
}