void
handle_ppp(netdissect_options *ndo, u_int proto, const u_char *p, u_int length)
{
	/*
	 * This is the top level routine for handling PPP-encapsulated
	 * packets.
	 */

	/*
	 * Is this a valid PPP packet?
	 * XXX - this check should be done in ppp_hdlc(), so that we
	 * don't do it twice.
	 */
	if ((proto & 0xff00) == 0x7e00) {
		/*
		 * Yes - this is a PPP packet.
		 * Strip off the PPP header.
		 */
		ppp_hdlc(ndo, p - 1, length);
		return;
	}

	/*
	 * No - this isn't a PPP packet.
	 * Is it a raw IP packet?
	 */
	if (proto == 0x0021) {
		/*
		 * Yes - call the regular IP parser.
		 */
		ip_print(ndo, p, length);
		return;
	}

	/*
	 * Is it a raw IPv6 packet?
	 */
	if (proto == 0x0057) {
		/*
		 * Yes - call the regular IPv6 parser.
		 */
		ip6_print(ndo, p, length);
		return;
	}

	/*
	 * Is it a raw IPX packet?
	 */
	if (proto == 0x002b) {
		/*
		 * Yes - call the regular IPX parser.
		 */
		ipx_print(ndo, p, length);
		return;
	}

	/*
	 * Is it a raw IPv4-over-ISO-8802-3 packet?
	 */
	if (proto == 0x002f) {
		/*
		 * Yes - call the regular IP parser.
		 */
		ip_print(ndo, p, length);
		return;
	}

	/*
	 * Is it a raw IPv6-over-ISO-8802-3 packet?
	 */
	if (proto == 0x0023) {
		/*
		 * Yes - call the regular IPv6 parser.
		 */
		isoclns_print(ndo, p, length, length);
		return;
	}

	/*
	 * Is it a raw IPX-over-ISO-8802-3 packet?
	 */
	if (proto == 0x8137) {
		/*
		 * Yes - call the regular IPX parser.
		 */
		ipx_print(ndo, p, length);
		return;
	}

	/*
	 * Is it a raw MPLS-over-ISO-8802-3 packet?
	 */
	if (proto == 0x8281) {
		/*
		 * Yes - call the regular MPLS parser.
		 */
		mpls_print(ndo, p, length);
		return;
	}

	/*
	 * Is it a raw MPLS-over-PPP packet?
	 */
	if (proto == 0x0281) {
		/*
		 * Yes - call the regular MPLS parser.
		 */
		mpls_print(ndo, p, length);
		return;
	}

	/*
	 * Is it a raw MPLS-over-MPLS-over-PPP packet?
	 */
	if (proto == 0x0283) {
		/*
		 * Yes - call the regular MPLS parser.
		 */
		mpls_print(ndo, p, length);
		return;
	}

	/*
	 * Is it a raw MLPPP packet?
	 */
	if (proto == 0x003d) {
		/*
		 * Yes - call the MLPPP parser.
		 */
		handle_mlppp(ndo, p, length);
		return;
	}

	/*
	 * Is it a raw compressed PPP packet?
	 */
	if (proto == 0x00fd) {
		/*
		 * Yes - print a message saying we got a compressed PPP
		 * packet.
		 */
		(*ndo->ndo_printf)(ndo, "compressed PPP data");
		return;
	}

	/*
	 * Is it a PPP control protocol?
	 */
	if (proto == 0x8005 ||
	    proto == 0x8021 ||
	    proto == 0x8023 ||
	    proto == 0x8057 ||
	    proto == 0x80fd) {
		/*
		 * Yes - call the PPP control protocol parser.
		 */
		handle_ctrl_proto(ndo, proto, p, length);
		return;
	}

	/*
	 * Is it a PAP packet?
	 */
	if (proto == 0xc023) {
		/*
		 * Yes - call the PAP parser.
		 */
		handle_pap(ndo, p, length);
		return;
	}

	/*
	 * Is it a CHAP packet?
	 */
	if (proto == 0xc223) {
		/*
		 * Yes - call the CHAP parser.
		 */
		handle_chap(ndo, p, length);
		return;
	}

	/*
	 * Is it a BAP packet?
	 */
	if (proto == 0xc02d) {
		/*
		 * Yes - call the BAP parser.
		 */
		handle_bap(ndo, p, length);
		return;
	}

	/*
	 * Is it a raw IPv6 packet?
	 */
	if (proto == 0x86dd) {
		/*
		 * Yes - call the regular IPv6 parser.
		 */
		ip6_print(ndo, p, length);
		return;
	}

	/*
	 * It's not a packet we recognize.
	 * Print a message saying we got an unknown PPP protocol,
	 * and print the packet's raw data.
	 */
	(*ndo->ndo_printf)(ndo, "%s ", tok2str(ppptype2str,"unknown PPP protocol (0x%04x)", proto));
	print_unknown_data(ndo, p, "\n\t", length);
	return;
}