int
mobility_opt_print(netdissect_options *ndo, const u_char *bp, u_int length)
{
	const u_char *ep;
	u_int optlen;
	u_int i;

	ep = bp + length;
	i = 0;
	while (i < length) {
		if (i + 1 > length)
			goto trunc;
		if (&bp[i + 1] > ndo->ndo_snapend - 1)
			goto trunc;
		if (bp[i] == 0) {
			optlen = 1;
		} else {
			if (i + 2 > length)
				goto trunc;
			if (&bp[i + 2] > ndo->ndo_snapend - 1)
				goto trunc;
			optlen = bp[i + 1] + 2;
		}
		if (i + optlen > length)
			goto trunc;
		if (&bp[i + optlen] > ndo->ndo_snapend - 1)
			goto trunc;
		switch (bp[i]) {

		case 0: /* Pad1 */
			(*ndo->ndo_printf)(ndo, "(pad1)");
			break;

		case 1: /* Padn */
			if (length - i < 2) {
				(*ndo->ndo_printf)(ndo, "(padn: trunc)");
				goto trunc;
			}
			(*ndo->ndo_printf)(ndo, "(padn)");
			break;

		case 2: /* Refresh */
			if (length - i < 4) {
				(*ndo->ndo_printf)(ndo, "(refresh: trunc)");
				goto trunc;
			}
			(*ndo->ndo_printf)(ndo, "(refresh: %u)",
			    EXTRACT_16BITS(&bp[i + 2]) * 4);
			break;

		case 3: /* Alternate Care-of Address */
			if (length - i < 18) {
				(*ndo->ndo_printf)(ndo, "(altcoa: trunc)");
				goto trunc;
			}
			(*ndo->ndo_printf)(ndo, "(alt-CoA: %s)",
			    getname6(ndo, &bp[i + 2]));
			break;

		case 4: /* Network Identifier */
			if (length - i < 6) {
				(*ndo->ndo_printf)(ndo, "(ni: trunc)");
				goto trunc;
			}
			(*ndo->ndo_printf)(ndo, "(ni: ho=0x%04x co=0x%04x)",
			    EXTRACT_16BITS(&bp[i + 2]),
			    EXTRACT_16BITS(&bp[i + 4]));
			break;

		case 5: /* IPv6 Mobility Authentication */
			if (length - i < 12) {
				(*ndo->ndo_printf)(ndo, "(auth: trunc)");
				goto trunc;
			}
			(*ndo->ndo_printf)(ndo, "(auth)");
			break;

		default:
			if (length - i < 2) {
				(*ndo->ndo_printf)(ndo, "(sopt_type %u: trunc)",
				    bp[i]);
				goto trunc;
			}
			(*ndo->ndo_printf)(ndo, "(type-0x%02x: len=%u)",
			    bp[i], bp[i + 1]);
			break;
		}
		i += optlen;
	}
	return 0;

trunc:
	return 1;
}