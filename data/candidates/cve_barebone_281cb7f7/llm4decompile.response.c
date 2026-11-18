int
dhcpv6_print(netdissect_options *ndo, const u_char *bp, u_int length, u_int indent)
{
	const u_char *cp;
	const u_char *ep;
	const u_char *op;
	u_int opt;
	u_int optlen;
	u_int i;

	cp = bp;
	while (cp < bp + length) {
		opt = *cp++;
		optlen = *cp++;
		optlen = (optlen << 8) | *cp++;
		cp++;
		(*ndo->ndo_printf)(ndo, "\n");
		for (i = indent; i != 0; i--)
			(*ndo->ndo_printf)(ndo, "\t");
		(*ndo->ndo_printf)(ndo, "%s", tok2str(dh6opt_str, "Unknown", opt));
		(*ndo->ndo_printf)(ndo, " (%u)", optlen + 4);
		switch (opt) {

		case DH6OPT_DNS_SERVERS:
		case DH6OPT_NTP_SERVERS:
			if (optlen % 16 != 0) {
				(*ndo->ndo_printf)(ndo, " %s",
				    " (invalid)");
				return -1;
			}
			for (i = 0; i < optlen; i += 16) {
				(*ndo->ndo_printf)(ndo, " %s",
				    getname6(ndo, cp + i));
			}
			break;

		case DH6OPT_DOMAIN_LIST:
			/* domain name(s) encoded as a sequence of
			 * domain labels */
			ep = cp + optlen;
			while (cp < ep) {
				(*ndo->ndo_printf)(ndo, " ");
				cp = ns_nprint(ndo, cp, ep);
				if (cp == NULL)
					return -1;
			}
			break;

		default:
			/* Just print the option data verbatim */
			op = cp;
			ep = cp + optlen;
			while (cp < ep) {
				(*ndo->ndo_printf)(ndo, " %02x", *cp++);
			}
			break;
		}
		cp += optlen;
	}
	return 0;
}