int __cdecl decode_rt_routing_info(netdissect_options *ndo, const u_char *pptr, char *buf, u_int buflen)
{
    u_int plen;
    u_int8_t route_target[8];
    size_t byte_len;
    uint32_t as_val;
    char *as_str;
    char *rd_str;

    // Check if ndo->ndo_snapend is NULL or wrapped, and if pptr is out of bounds
    if (ndo->ndo_snapend - 1 > ndo->ndo_snapend || pptr > ndo->ndo_snapend - 1)
        return -2;

    plen = *pptr;

    if (plen == 0) {
        snprintf(buf, buflen, "default route target");
        return 1;
    }

    if (plen < 32)
        return -1;

    plen -= 32;
    if (plen > 64)
        return -1;

    byte_len = (plen + 7) >> 3;

    // Bounds check: ensure reading byte_len bytes from pptr + 1 is safe
    if (ndo->ndo_snapend - byte_len > ndo->ndo_snapend || pptr + 1 > ndo->ndo_snapend - byte_len)
        return -2;

    memset(route_target, 0, sizeof(route_target));
    memcpy(route_target, pptr + 1, byte_len);

    // Mask off the trailing bits if plen is not a multiple of 8
    if ((plen & 7) != 0)
        route_target[byte_len - 1] &= (uint8_t)(0xFF00 >> (plen & 7));

    as_val = EXTRACT_32BITS(pptr + 1);
    as_str = as_printf(ndo, astostr, 20, as_val);
    rd_str = bgp_vpn_rd_print(ndo, route_target);

    snprintf(buf, buflen, "origin AS: %s, route target %s", as_str, rd_str);

    return byte_len + 5;
}