u_int
chdlc_print(netdissect_options *ndo, const u_char *p, u_int length)
{
	u_int caplen = length;
	u_int ethertype;
	const struct ip *ip;
	const struct ip6_hdr *ip6;

	ethertype = EXTRACT_16BITS(&p[2]);

	if (ndo->ndo_eflag) {
		(*ndo->ndo_printf)(ndo, "%s, ethertype %s (0x%04x), length %u: ",
		    tok2str(chdlc_cast_values, "0x%02x", p[0]),
		    tok2str(ethertype_values, "Unknown", ethertype),
		    ethertype, length);
	}

	length -= 4;
	p += 4;

	switch (ethertype) {

	case ETHERTYPE_IP:
		ip = (const struct ip *)p;
		ip_print(ndo, (const u_char *)ip, length);
		break;

	case ETHERTYPE_IPX:
		isoclns_print(ndo, p, length, (const u_char *)ndo->ndo_snapend - p);
		break;

	case ETHERTYPE_IPV6:
		ip6 = (const struct ip6_hdr *)p;
		ip6_print(ndo, (const u_char *)ip6, length);
		break;

	case 0x8847:
	case 0x8848:
		mpls_print(ndo, p, length);
		break;

	case 0x8035:
		chdlc_slarp_print(ndo, p, length);
		break;

	case 0xfefe:
		/*
		 * Cisco "proprietary" NetFlow.
		 *
		 * Reported by Arun Taneja <ataneja@cisco.com> as
		 * having an Ethertype of 0xfefe, with an initial
		 * octet of 0x81 for NetFlow v1, 0x82 for NetFlow
		 * v5, and 0x83 for NetFlow v9.
		 */
		switch (p[1]) {

		case 0x81:
			/*
			 * NetFlow v1.
			 */
			isoclns_print(ndo, &p[1], length - 1,
			    (const u_char *)ndo->ndo_snapend - &p[1]);
			break;

		case 0x82:
			/*
			 * NetFlow v5.
			 */
			isoclns_print(ndo, &p[1], length - 1,
			    (const u_char *)ndo->ndo_snapend - &p[1]);
			break;

		case 0x83:
			/*
			 * NetFlow v9.
			 */
			isoclns_print(ndo, &p[1], length - 1,
			    (const u_char *)ndo->ndo_snapend - &p[1]);
			break;

		default:
			/*
			 * Some other Cisco "proprietary" protocol
			 * using an Ethertype of 0xfefe.
			 */
			isoclns_print(ndo, p, length,
			    (const u_char *)ndo->ndo_snapend - p);
		}
		break;

	default:
		if (!ndo->ndo_eflag)
			(*ndo->ndo_printf)(ndo, "unknown CHDLC protocol (0x%04x)", ethertype);
	}

	return (caplen - length);
}