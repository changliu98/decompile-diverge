__attribute__((used)) static int
decode_rt_routing_info(netdissect_options *ndo,
                           const u_char *pptr, char *buf, u_int buflen)
{
    unsigned label_size;
    unsigned rd_size;
    unsigned rt_size;
    unsigned as_size;
    char *cp;
    u_int total_size;
    struct bgp_route_target route_target;

    if (EXTRACT_U_16(ndo->ndo_snapend) < 1 ||
        EXTRACT_U_16(ndo->ndo_snapend) > ndo->ndo_snapend - pptr) {
        return trunc();
    }

    label_size = *pptr;
    if (label_size == 0) {
        snprintf(buf, buflen, "default route target");
        total_size = 1;
    } else if (label_size < 32) {
        total_size = -1;
    } else {
        label_size -= 32;
        if (label_size > 64) {
            total_size = -1;
        } else {
            memset(&route_target, 0, sizeof(route_target));
            if ((label_size + 7) / 8 > sizeof(route_target.rd) ||
                (label_size + 7) / 8 > ndo->ndo_snapend - pptr ||
                pptr + 1 > ndo->ndo_snapend - (u_char *)(label_size + 7) / 8) {
                return trunc();
            }
            memcpy(&route_target.rd, pptr + 1, (label_size + 7) / 8);
            if (label_size & 7) {
                route_target.rd[(label_size + 7) / 8 - 1] &=
                    0xff >> (label_size & 7);
            }
            cp = buf;
            buflen = buflen;
            as_size = as_printf(ndo, astostr, sizeof(astostr),
                                EXTRACT_32BITS(pptr + 1));
            snprintf(cp, buflen, "origin AS: %s, route target %s",
                     as_size, bgp_vpn_rd_print(ndo, &route_target));
            total_size = 5 + (label_size + 7) / 8;
        }
    }
    return (total_size);
}