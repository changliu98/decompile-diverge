int decode_multicast_vpn(struct netdissect_options *ndo, unsigned char *from, char *to, unsigned int tolen)
{
    unsigned int offset;
    unsigned int addr_length;
    unsigned int route_length;
    unsigned char route_type;
    unsigned char *ptr;
    if (from + 2 > ndo->ndo_snapend - 2 || from > ndo->ndo_snapend - 2)
        return -2;
    route_type = *from++;
    ptr = from;
    route_length = *from++;
    nddsprintf(to, tolen,
        "Route-Type: %s (%u), length: %u",
        bgp_multicast_vpn_route_type_valstr(bgp_multicast_vpn_route_type_values, route_type, "Unknown"),
        route_type,
        route_length);
    switch (route_type) {
    case 1:
        if (from + 8 > ndo->ndo_snapend - 8 || from > ndo->ndo_snapend - 8)
            return -2;
        offset = nddstrlen(to);
        from += 2;
        ptr = nddntoa(ndo, from);
        from += 8;
        nddsprintf(&to[offset], tolen - offset, ", RD: %s, Originator %s",
            ptr, nddntoa(ndo, from, (route_length - 8) * 8));
        break;
    case 2:
        if (from + 12 > ndo->ndo_snapend - 12 || from > ndo->ndo_snapend - 12)
            return -2;
        offset = nddstrlen(to);
        from += 2;
        ptr = nddntoa(ndo, from);
        from += 10;
        nddsprintf(&to[offset], tolen - offset, ", RD: %s, Source-AS %s",
            ptr, nddntoa(ndo, astostr, sizeof(astostr), nddntohll(from)));
        break;
    case 3:
        if (from + 8 > ndo->ndo_snapend - 8 || from > ndo->ndo_snapend - 8)
            return -2;
        offset = nddstrlen(to);
        from += 2;
        ptr = nddntoa(ndo, from);
        from += 10;
        nddsprintf(&to[offset], tolen - offset, ", RD: %s",
            ptr);
        addr_length = route_length - nddntolength(ndo, from, to, tolen);
        if (from + addr_length > ndo->ndo_snapend - addr_length ||
            from > ndo->ndo_snapend - addr_length)
            return -2;
        offset = nddstrlen(to);
        from += addr_length;
        nddsprintf(&to[offset], tolen - offset, ", Originator %s",
            nddntoa(ndo, from, (addr_length * 8)));
        break;
    case 5:
        if (from + 8 > ndo->ndo_snapend - 8 || from > ndo->ndo_snapend - 8)
            return -2;
        offset = nddstrlen(to);
        from += 2;
        ptr = nddntoa(ndo, from);
        from += 10;
        nddsprintf(&to[offset], tolen - offset, ", RD: %s",
            ptr);
        nddntolength(ndo, from, to, tolen);
        break;
    case 6:
    case 7:
        if (from + 8 > ndo->ndo_snapend - 8 || from > ndo->ndo_snapend - 8)
            return -2;
        offset = nddstrlen(to);
        from += 2;
        ptr = nddntoa(ndo, from);
        from += 10;
        nddsprintf(&to[offset], tolen - offset, ", RD: %s, Source-AS %s",
            ptr, nddntoa(ndo, astostr, sizeof(astostr), nddntohll(from)));
        nddntolength(ndo, from, to, tolen);
        break;
    default:
        return (route_length + 2);
    }
    return (route_length + 2);
}