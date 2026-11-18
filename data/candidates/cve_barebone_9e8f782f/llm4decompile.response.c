void
isoclns_print(netdissect_options *ndo, const u_char *p, u_int length, u_int caplen)
{
	if (caplen < 2) {
		ndo->ndo_printf(ndo, "|OSI");
		return;
	}
	if (ndo->ndo_eflag)
		ndo->ndo_printf(ndo, "OSI NLPID %s (0x%02x): ",
		    tok2str(nlpid_values, "Unknown", *p), *p);
	if (*p == 0x00) {
		/*
		 * Null LSAP.
		 */
		ndo->ndo_printf(ndo, "%slength: %u", ndo->ndo_eflag ? "\n\t" : "", length);
		return;
	}
	if (*p == 0x08) {
		/*
		 * Q.933
		 */
		q933_print(ndo, p + 1, length - 1);
		return;
	}
	if (*p == 0x81) {
		/*
		 * CLNP.
		 */
		if (!clnp_print(ndo, p, length))
			print_unknown_data(ndo, p, "\n\t", caplen);
		return;
	}
	if (*p == 0x82) {
		/*
		 * ES-IS.
		 */
		esis_print(ndo, p, length);
		return;
	}
	if (*p == 0x83) {
		/*
		 * IS-IS.
		 */
		if (!isis_print(ndo, p, length))
			print_unknown_data(ndo, p, "\n\t", caplen);
		return;
	}
	if (*p == 0x8e) {
		/*
		 * IPv6.
		 */
		ip6_print(ndo, p + 1, length - 1);
		return;
	}
	if (*p == 0xcc) {
		/*
		 * IPv4.
		 */
		ip_print(ndo, p + 1, length - 1);
		return;
	}
	if (*p == 0xcf) {
		/*
		 * PPP.
		 */
		ppp_print(ndo, p + 1, length - 1);
		return;
	}
	if (!ndo->ndo_eflag)
		ndo->ndo_printf(ndo, "OSI NLPID 0x%02x unknown", *p);
	ndo->ndo_printf(ndo, "%slength: %u", ndo->ndo_eflag ? "\n\t" : "", length);
	if (caplen > 1)
		print_unknown_data(ndo, p, "\n\t", caplen);
}