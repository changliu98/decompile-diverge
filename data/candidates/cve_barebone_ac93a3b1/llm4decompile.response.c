int
mp_dss_print(netdissect_options *ndo, const u_char *bp, u_int length, u_char flags)
{
	const mp_dss *mp = (const mp_dss *)bp;
	const u_char *cp;
	u_int hlen;

	if (length != mp_dss_len(mp, 1) && length != mp_dss_len(mp, 0))
		return 0;

	if (flags & 0x02)
		return 0;

	if (mp->flags & 0x10)
		(*ndo->ndo_printf)(ndo, " fin");
	cp = (const u_char *)(mp + 1);
	if (mp->flags & 0x01) {
		(*ndo->ndo_printf)(ndo, " ack ");
		if (mp->flags & 0x02) {
			(*ndo->ndo_printf)(ndo, "%lu",
			    (unsigned long)EXTRACT_64BITS(cp));
			cp += 8;
		} else {
			(*ndo->ndo_printf)(ndo, "%u", EXTRACT_32BITS(cp));
			cp += 4;
		}
	}
	if (mp->flags & 0x04) {
		(*ndo->ndo_printf)(ndo, " seq ");
		if (mp->flags & 0x08) {
			(*ndo->ndo_printf)(ndo, "%lu",
			    (unsigned long)EXTRACT_64BITS(cp));
			cp += 8;
		} else {
			(*ndo->ndo_printf)(ndo, "%u", EXTRACT_32BITS(cp));
			cp += 4;
		}
		(*ndo->ndo_printf)(ndo, " subseq %u", EXTRACT_32BITS(cp));
		cp += 4;
		(*ndo->ndo_printf)(ndo, " len %u", EXTRACT_16BITS(cp));
		cp += 2;
		hlen = mp_dss_len(mp, 1);
		if (length == hlen) {
			(*ndo->ndo_printf)(ndo, " csum 0x%x",
			    EXTRACT_16BITS(cp));
		}
	}
	return 1;
}