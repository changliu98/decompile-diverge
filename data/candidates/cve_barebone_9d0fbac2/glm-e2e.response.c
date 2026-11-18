void handle_ppp(struct netdissect_options *ndo, uint32_t proto, const uint8_t *p, int length) {
    if ((proto & 0xff00) == 0x7e00) {
        ppp_hdlc(ndo, p - 1, length);
        return;
    }

    switch (proto) {
        case 0x21:
        case 0x2f:
        case 0x800:
            ip_print(ndo, p, length);
            break;
        case 0x23:
            isoclns_print(ndo, p, length, length);
            break;
        case 0x2b:
        case 0x8137:
            ipx_print(ndo, p, length);
            break;
        case 0x3d:
            handle_mlppp(ndo, p, length);
            break;
        case 0x57:
        case 0x86dd:
            ip6_print(ndo, p, length);
            break;
        case 0xfd:
            ndo->printf_func("PPP-MP");
            break;
        case 0x281:
        case 0x283:
            mpls_print(ndo, p, length);
            break;
        case 0x8021:
        case 0x8023:
        case 0x8057:
        case 0x80fd:
        case 0x8281:
        case 0xc021:
        case 0xc02b:
            handle_ctrl_proto(ndo, proto, p, length);
            break;
        case 0xc023:
            handle_pap(ndo, p, length);
            break;
        case 0xc02d:
            handle_bap(ndo, p, length);
            break;
        case 0xc223:
            handle_chap(ndo, p, length);
            break;
        default:
            const char *proto_str = tok2str(ppptype2str, "unknown PPP protocol (0x%04x)", proto);
            ndo->printf_func("%s", proto_str);
            print_unknown_data(ndo, p, "\n\t", length);
            break;
    }
}