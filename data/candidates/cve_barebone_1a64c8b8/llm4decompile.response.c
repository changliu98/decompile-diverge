int
dhcpv4_print(netdissect_options *ndo, const u_char *bp, u_int length, u_int indent)
{
	const struct dhcpv4_packet *dp = (const struct dhcpv4_packet *)bp;
	const u_char *cp;
	const u_char *ep;
	u_int i;
	u_char type;
	u_char optlen;
	const char *name;

	cp = (const u_char *)dp;
	ep = cp + length;

	for (i = 0; i < length; ) {
		type = cp[0];
		optlen = cp[1];
		cp += 2;
		(*ndo->ndo_printf)(ndo, "\n");
		for (t = indent; t != 0; t--)
			(*ndo->ndo_printf)(ndo, "\t");
		(*ndo->ndo_printf)(ndo, "%s", tok2str(dh4opt_str, "Unknown", type));
		(*ndo->ndo_printf)(ndo, " (%u)", optlen + 2);
		switch (type) {

		case 53: /* DHCP Message Type Option */
			(*ndo->ndo_printf)(ndo, " %s",
			    tok2str(dh4msg_str, "Unknown", *cp));
			break;

		case 55: /* Parameter Request List */
		case 50: /* Requested IP Address */
			if (optlen < 4 || optlen % 4 != 0)
				return -1;
			for (t = 0; t < optlen; t += 4)
				(*ndo->ndo_printf)(ndo, " %s", getname(ndo, cp + t));
			break;

		case 51: /* IP Address Lease Time */
		case 52: /* IP Address Lease Time */
		case 54: /* DHCP Server Identifier */
		case 56: /* DHCP Message */
		case 57: /* DHCP Maximum Message Size */
		case 58: /* Renewal Time Value */
		case 59: /* Rebinding Time Value */
		case 60: /* Class Identifier */
		case 61: /* Client Identifier */
			break;

		case 64: /* DHCP NTP Servers */
			if (optlen < 4 || optlen % 4 != 0)
				return -1;
			for (t = 0; t < optlen; t += 4) {
				struct in_addr addr;

				addr.s_addr = *((const u_int32_t *)(cp + t));
				(*ndo->ndo_printf)(ndo, " %s", (*ndo->ndo_inet_ntoa)(&addr));
			}
			break;

		case 66: /* TFTP Server Name */
		case 67: /* Bootfile name */
		case 68: /* Domain Name Server */
		case 69: /* Log Server */
		case 70: /* Cookie Server */
		case 71: /* LPR Server */
		case 72: /* Impress Server */
		case 73: /* Resource Location Server */
		case 74: /* Host Name Server */
			while (cp < ep) {
				(*ndo->ndo_printf)(ndo, " ");
				cp = ns_nprint(ndo, cp, ep);
				if (cp == NULL)
					return -1;
			}
			break;

		case 82: /* DHCP Relay Agent Information */
			while (cp < ep) {
				u_char tlvtype;
				u_char tlvlen;
				const u_char *tlv;

				tlvtype = *cp++;
				tlvlen = *cp++;
				tlv = cp;
				cp += tlvlen;
				(*ndo->ndo_printf)(ndo, "\n");
				for (t = indent; t != 0; t--)
					(*ndo->ndo_printf)(ndo, "\t");
				(*ndo->ndo_printf)(ndo, "  %s",
				    tok2str(dh4tlv_str, "Unknown", tlvtype));
				(*ndo->ndo_printf)(ndo, " (%u)", tlvlen);
				switch (tlvtype) {

				case 1: /* Agent Circuit ID */
					(*ndo->ndo_printf)(ndo, " ");
					(*ndo->ndo_printf)(ndo, "%s",
					    etheraddr_string(tlv));
					break;

				case 2: /* Agent Remote ID */
					(*ndo->ndo_printf)(ndo, " ");
					(*ndo->ndo_printf)(ndo, "%s",
					    etheraddr_string(tlv));
					break;

				case 3: /* Agent Remote ID */
					while (tlv < cp) {
						struct in_addr addr;

						addr.s_addr =
						    *((const u_int32_t *)(tlv));
						tlv += 4;
						(*ndo->ndo_printf)(ndo, " %s",
						    (*ndo->ndo_inet_ntoa)(&addr));
					}
					break;
				}
			}
			break;

		default:
			break;
		}
		i += optlen + 2;
	}
	return 0;
trunc:
	return -1;
}