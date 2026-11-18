int __cdecl xid_map_enter(netdissect_options *ndo, const sunrpc_msg *rp, const u_char *bp)
{
    xid_map_entry *xmep;
    const ip6_hdr *ip6 = NULL;
    const ip *ip4 = NULL;

    // Bounds check: ensure we can safely read 4 bytes past the reject union
    if (ndo->ndo_snapend - 4 > ndo->ndo_snapend ||
        (const u_char *)&rp->ru.RM_rmb.rp_reject.ru > ndo->ndo_snapend - 4)
        return 0;

    // Determine IP version from the first nibble of the packet
    uint8_t ip_ver = *bp >> 4;
    if (ip_ver == 4) {
        ip4 = (const ip *)bp;
    } else if (ip_ver == 6) {
        ip6 = (const ip6_hdr *)bp;
    } else {
        return 1;
    }

    // Insert into circular buffer (size 64)
    xmep = &xid_map[xid_map_next++];
    if (xid_map_next >= 64)
        xid_map_next = 0;

    xmep->xid = rp->rm_xid;

    if (ip4) {
        xmep->ipver = 4;
        // IPv4 addresses are stored in the first 32 bits of the IPv6 union
        xmep->client.__in6_u.__u6_addr32[0] = (uint32_t)ip4->ip_src;
        xmep->server.__in6_u.__u6_addr32[0] = (uint32_t)ip4->ip_dst;
    } else if (ip6) {
        xmep->ipver = 6;
        // Fast 64-bit copies for IPv6 addresses
        *(uint64_t *)xmep->client.__in6_u.__u6_addr8 = *(const uint64_t *)ip6->ip6_src.__in6_u.__u6_addr8;
        *(uint64_t *)&xmep->client.__in6_u.__u6_addr32[2] = *(const uint64_t *)&ip6->ip6_src.__in6_u.__u6_addr32[2];
        *(uint64_t *)xmep->server.__in6_u.__u6_addr8 = *(const uint64_t *)ip6->ip6_dst.__in6_u.__u6_addr8;
        *(uint64_t *)&xmep->server.__in6_u.__u6_addr32[2] = *(const uint64_t *)&ip6->ip6_dst.__in6_u.__u6_addr32[2];
    }

    // Extract RPC procedure and version from the rejected reply message
    xmep->proc = EXTRACT_32BITS((const char *)&rp->ru.RM_rmb.rp_reject.ru + 4);
    xmep->vers = EXTRACT_32BITS(&rp->ru.RM_rmb.rp_reject.ru);

    return 1;
}