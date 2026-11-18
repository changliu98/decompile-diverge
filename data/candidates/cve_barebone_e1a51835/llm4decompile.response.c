void
aodv_extension(netdissect_options *ndo,
	       register const u_char *bp, u_int length)
{
	register u_int caplen = ndo->ndo_caplen;
	register u_int length_remaining;
	register const struct aodv_ext *ep;

	ep = (const struct aodv_ext *)bp;

	if (ep->type == 1) {	/* RFC 5054 */
		ah = (const struct aodv_hello *)bp;
		length_remaining = length;
		if (&ah->interval > (const u_char *)ndo->ndo_snapend - (const u_char *)&ah->interval ||
		    (const u_char *)&ah->interval > (const u_char *)ndo->ndo_snapend ||
		    length < sizeof(*ah)) {
			(*ndo->ndo_printf)(ndo, " [|hello]");
			return;
		}
		(*ndo->ndo_printf)(ndo, "\n\text HELLO %ld ms",
				   ((ah->interval << 24) |
				    (ah->interval << 16) |
				    (ah->interval << 8) |
				    (ah->interval)));
		return;
	}
	(*ndo->ndo_printf)(ndo, "\n\text %u %u", ep->type, ep->length);
}