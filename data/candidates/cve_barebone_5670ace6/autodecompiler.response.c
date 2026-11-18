void
vrrp_print(netdissect_options *ndo,
           register const u_char *bp, register u_int length, register u_int af, register u_int ttl)
{
    unsigned i;
    int vrid, priority, auth_type = 0, naddr, type, ver;
    char c;

    if (length < 1 || length < (unsigned)(bp[0] - 1))
        goto trunc;
    ver = (bp[0] & 0xf0) >> 4;
    type = bp[0] & 0x0f;
    ND_PRINT((ndo, "VRRPv%u, %s", ver, tok2str(type2str, "unknown type (%u)", type)));
    if (ttl != 255)
        ND_PRINT((ndo, ", (ttl %u)", ttl));
    if (ver < 2 || ver > 3 || type != 1)
        goto done;
    if (length < 2 || length < (unsigned)(bp[0] - 1))
        goto trunc;
    vrid = bp[1];
    priority = bp[2];
    ND_PRINT((ndo, ", vrid %u, prio %u", vrid, priority));
    if (length < 5 || length < (unsigned)(bp[0] - 1))
        goto trunc;
    if (ver == 2) {
        auth_type = bp[4];
        ND_PRINT((ndo, ", authtype %s", tok2str(auth2str, "unknown auth type (%u)", auth_type)));
        ND_PRINT((ndo, ", intvl %us, length %u", bp[5], length));
    } else {
        unsigned interval;

        interval = (bp[4] & 0x0f) << 8 | bp[5];
        ND_PRINT((ndo, ", intvl %ucs, length %u", interval, length));
    }
    if (!ndo->ndo_vflag)
        goto done;
    naddr = bp[3];
    if ((ver == 2 && (length < 8 || length < (unsigned)(bp[0] - 1))) ||
        (ver == 3 && (length < 9 || length < (unsigned)(bp[0] - 1))))
        goto trunc;
    if (nextproto4_cksum(ndo, af, bp, length, length, IPPROTO_VRRP) != 0)
        ND_PRINT((ndo, ", (bad vrrp cksum %x)", EXTRACT_16BITS(&bp[6])));
    else if (ver == 2 && auth_type == 1) {
        if (length < 9 || length < (unsigned)(bp[0] - 1))
            goto trunc;
        ND_PRINT((ndo, " auth "));
        if (fn_printn(ndo, &bp[7], 8, ndo->ndo_snapend)) {
            ND_PRINT((ndo, "\""));
            goto trunc;
        }
        ND_PRINT((ndo, "\""));
    }
    goto done;
trunc:
    ND_PRINT((ndo, "[|vrrp]"));
done:
    return;
}