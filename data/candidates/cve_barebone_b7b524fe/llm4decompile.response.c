int
ospf6_decode_v3(netdissect_options *ndo, const ospf6hdr *op,
    const u_char *dataend)
{
	const u_char *cp;
	const rtrid_t *ap;
	const lsa6 *lsap;
	const lsa6_hdr *lshp;
	const lsr6 *lsrp;
	const dd6 *ddp;
	const hello6 *hellop;
	const lsu6 *lsup;
	uint32_t count;
	uint16_t mtu;
	uint32_t seq;
	uint16_t ht, dt;
	int i;

	switch (op->ospf6_type) {

	case 1: /* Hello */
		hellop = (const hello6 *)(op + 1);
		(*ndo->ndo_printf)(ndo, "\n\tOptions [%s]",
		    bittok2str(ospf6_option_values, "none",
		    EXTRACT_32BITS(&hellop->h_options)));
		if (&hellop->h_deadtimer > ndo->ndo_snapend - 2 ||
		    &hellop->h_areaid > ndo->ndo_snapend - 2)
			return (1);
		ht = EXTRACT_16BITS(&hellop->h_deadtimer);
		dt = EXTRACT_16BITS(&hellop->h_areaid);
		(*ndo->ndo_printf)(ndo,
		    "\n\t  Hello Timer %us, Dead Timer %us, Interface-ID %s, Priority %u",
		    ht, dt, getname(ndo, (const char *)&hellop->h_routerid),
		    hellop->h_priority);
		if (&hellop->h_dr > ndo->ndo_snapend - 4 ||
		    &hellop->h_bdr > ndo->ndo_snapend - 4)
			return (1);
		if (EXTRACT_32BITS(&hellop->h_dr))
			(*ndo->ndo_printf)(ndo, "\n\t  Designated Router %s",
			    getname(ndo, (const char *)&hellop->h_dr));
		if (&hellop->h_bdr > ndo->ndo_snapend - 4 ||
		    &hellop->h_seqnum > ndo->ndo_snapend - 4)
			return (1);
		if (EXTRACT_32BITS(&hellop->h_bdr))
			(*ndo->ndo_printf)(ndo,
			    ", Backup Designated Router %s",
			    getname(ndo, (const char *)&hellop->h_bdr));
		if (ndo->ndo_vflag < 2)
			return (0);
		(*ndo->ndo_printf)(ndo, "\n\t  Neighbor List:");
		ap = (const rtrid_t *)&hellop->h_seqnum;
		while (ap < dataend) {
			if (&ap->router > ndo->ndo_snapend - sizeof(rtrid_t))
				return (1);
			(*ndo->ndo_printf)(ndo, "\n\t    %s",
			    getname(ndo, (const char *)&ap->router));
			ap++;
		}
		break;

	case 2: /* Database Description */
		ddp = (const dd6 *)(op + 1);
		if (&ddp->dd_options > ndo->ndo_snapend - 4 ||
		    &ddp->dd_seqnum > ndo->ndo_snapend - 4)
			return (1);
		(*ndo->ndo_printf)(ndo, "\n\tOptions [%s]",
		    bittok2str(ospf6_option_values