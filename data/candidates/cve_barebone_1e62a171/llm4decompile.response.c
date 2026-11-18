int
name_len(netdissect_options *ndo, const u_char *cp, const u_char *maxbuf)
{
	register const u_char *cp0;
	register u_int i;

	cp0 = cp;
	if (cp >= maxbuf)
		return(-1);
	if (cp > ndo->ndo_snapend - 1 || cp > ndo->ndo_snapend - 1)
		return(-1);
	if ((*cp & 0xc0) == 0xc0)
		return(2);
	for (i = 0; (int)*cp != 0; i += *cp + 1) {
		if (cp >= maxbuf)
			return(-1);
		if (cp > ndo->ndo_snapend - 1 || cp > ndo->ndo_snapend - 1)
			return(-1);
		cp += *cp + 1;
	}
	return(i + 1);
}