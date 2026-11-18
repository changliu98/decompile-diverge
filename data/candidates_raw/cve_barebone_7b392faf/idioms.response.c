static int xid_map_add(struct netdissect_options *ndo, struct sunrpc_msg *rp, unsigned char *bp)
{
    struct xid_map_entry *xmep;
    struct ip *ip = ((void *)0);
    struct ip6_hdr *ip6 = ((void *)0);
    unsigned int ipver;
    if (bp + 4 > ndo->ndo_snapend ||
        bp + rp->ru.RM_rmb.rp_reject.ru.rj_vers + 4 > ndo->ndo_snapend)
        return (0);
    ipver = (bp[0] >> 4);
    if (ipver == 4)
        ip = (struct ip *)bp;
    else if (ipver == 6)
        ip6 = (struct ip6_hdr *)bp;
    else
        return (1);
    xmep = &xid_map[xid_map_next];
    xid_map_next++;
    if (xid_map_next >= (sizeof(xid_map) / sizeof((xid_map)[0])))
        xid_map_next = 0;
    xmep->xid = rp->rm_xid;
    if (ip) {
        xmep->ipver = 4;
        memcpy(&xmep->client.ip4, &ip->ip_src, sizeof(ip->ip_src));
        memcpy(&xmep->server.ip4, &ip->ip_dst, sizeof(ip->ip_dst));
    } else if (ip6) {
        xmep->ipver = 6;
        memcpy(&xmep->client.ip6, &ip6->ip6_src, sizeof(ip6->ip6_src));
        memcpy(&xmep->server.ip6, &ip6->ip6_dst, sizeof(ip6->ip6_dst));
    }
    xmep->proc = xdr_ntoh32((unsigned int *)&rp->ru.RM_rmb.rp_reject.ru.rj_proc);
    xmep->vers = xdr_ntoh32((unsigned int *)&rp->ru.RM_rmb.rp_reject.ru.rj_vers);
    return (1);
}