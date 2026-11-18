int
frag6_print(netdissect_options *ndo, const u_char *bp, const u_char *bp2)
{
	const struct ip6_frag *dp;
	const struct ip6_hdr *ip6;
	u_int length;

	if (ndo->ndo_snapend < bp + 2 ||
	    ndo->ndo_snapend - 2 < bp2 + sizeof(struct ip6_hdr)) {
		(*ndo->ndo_printf)(ndo, "[|frag]");
		return(-1);
	}

	dp = (const struct ip6_frag *)(bp + 2);
	ip6 = (const struct ip6_hdr *)bp2;

	if (ndo->ndo_vflag)
		(*ndo->ndo_printf)(ndo, "frag (0x%08x:%d|%ld)",
		    EXTRACT_32BITS(&dp->ip6f_ident),
		    EXTRACT_16BITS(&dp->ip6f_offlg) & 0xfff8,
		    (u_long)(EXTRACT_16BITS(&ip6->ip6_plen) - (bp - bp2) -
		    sizeof(struct ip6_hdr) + 32));
	else
		(*ndo->ndo_printf)(ndo, "frag (%d|%ld)",
		    EXTRACT_16BITS(&dp->ip6f_offlg) & 0xfff8,
		    (u_long)(EXTRACT_16BITS(&ip6->ip6_plen) - (bp - bp2) -
		    sizeof(struct ip6_hdr) + 32));

	length = 8;
	if ((EXTRACT_16BITS(&dp->ip6f_offlg) & 0xfff8) == 0) {
		(*ndo->ndo_printf)(ndo, " ");
		length = 8;
	} else
		length = -1;

	return(length);
}