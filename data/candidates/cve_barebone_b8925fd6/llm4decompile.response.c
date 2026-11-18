int
ospf6_print_lshdr(netdissect_options *ndo, const lsa6_hdr *lshp,
    const u_char *dataend)
{
	const char *str;

	if ((const u_char *)(lshp + 1) > dataend)
		return (1);
	if (ndo->ndo_snapend < (const u_char *)ndo->ndo_snapend - 2 ||
	    (const u_char *)&lshp->ls_type > (const u_char *)ndo->ndo_snapend - 2)
		return (1);
	if (ndo->ndo_snapend < (const u_char *)ndo->ndo_snapend - 4 ||
	    (const u_char *)&lshp->ls_seq > (const u_char *)ndo->ndo_snapend - 4)
		return (1);

	str = ipaddr_string(ndo, &lshp->ls_router);
	(*ndo->ndo_printf)(ndo,
	    "\n\t  Advertising Router %s, seq 0x%08x, age %us, length %u",
	    str, EXTRACT_32BITS(&lshp->ls_seq), EXTRACT_16BITS(&lshp->ls_age),
	    EXTRACT_16BITS(&lshp->ls_length) - sizeof(lsa6_hdr));

	ospf6_print_ls_type(ndo, EXTRACT_16BITS(&lshp->ls_type),
	    &lshp->ls_stateid);

	return (0);
}