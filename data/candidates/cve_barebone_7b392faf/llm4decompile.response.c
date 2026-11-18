int
xid_map_enter(netdissect_options *ndo, const struct sunrpc_msg *rp,
    const u_char *bp)
{
	register const struct ip *ip = NULL;
	register const struct ip6_hdr *ip6 = NULL;
	register u_int i;

	if (ndo->ndo_snapend < (bp + sizeof(struct ip)) ||
	    ndo->ndo_snapend < (bp + sizeof(struct ip6_hdr)))
		return 0;

	if ((*bp >> 4) == 0x4)
		ip = (const struct ip *)bp;
	else if ((*bp >> 4) == 0x6)
		ip6 = (const struct ip6_hdr *)bp;
	else
		return 1;

	i = xid_map_next++;
	if (xid_map_next >= 64)
		xid_map_next = 0;
	xid_map[i].xid = rp->rm_xid;
	if (ip != NULL) {
		xid_map[i].ipver = 4;
		xid_map[i].client.addr4 = ip->ip_src;
		xid_map[i].server.addr4 = ip->ip_dst;
	} else if (ip6 != NULL) {
		xid_map[i].ipver = 6;
		xid_map[i].client.addr6 = ip6->ip6_src;
		xid_map[i].server.addr6 = ip6->ip6_dst;
	}
	xid_map[i].proc = EXTRACT_32BITS(&rp->rm_call.cb_proc);
	xid_map[i].vers = EXTRACT_32BITS(&rp->rm_call.cb_vers);
	return 1;
}