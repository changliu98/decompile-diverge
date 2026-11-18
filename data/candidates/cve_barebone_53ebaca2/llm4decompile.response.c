void
isakmp_rfc3948_print(netdissect_options *ndo,
		      const u_char *bp, u_int length, const u_char *bp2)
{
	int enh, padlen;
	int advance;

	if (length == 1 && bp[0] == 0xff) {
		/*
		 * This is a keep-alive packet.
		 */
		(*ndo->ndo_printf)(ndo, "isakmp-nat-keep-alive");
		return;
	}

	if (length < 4) {
		(*ndo->ndo_printf)(ndo, "[|isakmp]");
		return;
	}

	if (bp[0] == 0 && bp[1] == 0 && bp[2] == 0 && bp[3] == 0) {
		/*
		 * This is a non-ESP encapsulated packet.
		 */
		(*ndo->ndo_printf)(ndo, "NONESP-encap: ");
		isakmp_print(ndo, bp + 4, length - 4, bp2);
		return;
	}

	/*
	 * This is an ESP encapsulated packet.
	 */
	(*ndo->ndo_printf)(ndo, "UDP-encap: ");
	advance = esp_print(ndo, bp, length, bp2, &enh, &padlen);
	if (advance > 0) {
		bp += advance;
		length -= advance + padlen;
		nh = enh & 0xff;
		ip_print_inner(ndo, bp, length, nh, bp2);
	}
}