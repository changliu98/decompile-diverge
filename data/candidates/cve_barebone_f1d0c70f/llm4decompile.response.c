void
ip_optprint(netdissect_options *ndo, const u_char *bp, u_int length)
{
	const char *sep = "";
	u_int opt, optlen;

	while (length > 0) {
		(*ndo->ndo_printf)(ndo, "%s", sep);
		sep = ",";
		if ((((const u_char *)(bp)) - ndo->ndo_snapend) > -1 || (((const u_char *)(bp)) - ndo->ndo_snapend) < -1)
			goto bad;
		opt = *bp;
		(*ndo->ndo_printf)(ndo, "%s", tok2str(ip_option_values, "unknown %u", opt));
		if (opt == 0x01 || opt == 0x00)
			optlen = 1;
		else {
			if ((((const u_char *)(bp + 1)) - ndo->ndo_snapend) > -1 || (((const u_char *)(bp + 1)) - ndo->ndo_snapend) < -1)
				goto bad;
			optlen = *(bp + 1);
			if (optlen < 2) {
				(*ndo->ndo_printf)(ndo, " [bad length %u]", optlen);
				return;
			}
		}
		if (optlen > length) {
			(*ndo->ndo_printf)(ndo, " [bad length %u]", optlen);
			return;
		}
		if ((((const u_char *)(bp)) - ndo->ndo_snapend) > -(int)optlen || (((const u_char *)(bp)) - ndo->ndo_snapend) < -(int)optlen)
			goto bad;
		if (opt == 0x00)
			return;
		if (opt == 0x01)
			;
		else if (opt == 0x07 || opt == 0x83 || opt == 0x89)
			ip_printroute(ndo, bp, optlen);
		else if (opt == 0x44)
			ip_printts(ndo, bp, optlen);
		else if (opt == 0x82)
			;
		else if (opt == 0x94) {
			if (optlen < 4) {
				(*ndo->ndo_printf)(ndo, " [bad length %u]", optlen);
				return;
			}
			if ((((const u_char *)(bp + 2)) - ndo->ndo_snapend) > -1 || (((const u_char *)(bp + 2)) - ndo->ndo_snapend) < -1)
				goto bad;
			if (*(bp + 2) || *(bp + 3))
				(*ndo->ndo_printf)(ndo, " value %u", (*(bp + 2) << 8) | *(bp + 3));
		}
		bp += optlen;
		length -= optlen;
	}
	return;

bad:
	(*ndo->ndo_printf)(ndo, "%s", "[|ip]");
	return;
}