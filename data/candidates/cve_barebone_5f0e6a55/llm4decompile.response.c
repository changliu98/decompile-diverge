u_int
ieee802_15_4_if_print(netdissect_options *ndo, const struct pcap_pkthdr *h, const u_char *p)
{
	u_int length = 3;
	u_int caplen = h->caplen;
	u_int hdrlen = 0;
	u_short fc, destpanid = 0;
	u_char seq;

	if (caplen < 3) {
		(*ndo->ndo_printf)(ndo, "[|802.15.4]");
		return 3;
	}

	fc = p[0] | (p[1] << 8);
	seq = p[2];
	p += 3;
	caplen -= 3;
	hdrlen += 3;

	(*ndo->ndo_printf)(ndo, "IEEE 802.15.4 %s packet ", ftypes[fc & 0x7]);

	if (ndo->ndo_vflag)
		(*ndo->ndo_printf)(ndo, "seq %02x ", seq);

	switch ((fc >> 10) & 0x3) {

	case 0:
		if (fc & 0x40) {
			(*ndo->ndo_printf)(ndo, "[|802.15.4]");
			return 3;
		}
		if (ndo->ndo_vflag)
			(*ndo->ndo_printf)(ndo, "none ");
		break;

	case 1:
		if (ndo->ndo_vflag)
			(*ndo->ndo_printf)(ndo, "reserved destination "
			    "addressing mode");
		return 3;

	case 2:
		if (caplen < 2) {
			(*ndo->ndo_printf)(ndo, "[|802.15.4]");
			return 3;
		}
		destpanid = p[0] | (p[1] << 8);
		p += 2;
		caplen -= 2;
		hdrlen += 2;
		if (caplen < 2) {
			(*ndo->ndo_printf)(ndo, "[|802.15.4]");
			return 5;
		}
		if (ndo->ndo_vflag)
			(*ndo->ndo_printf)(ndo, "%04x:%04x ", destpanid,
			    p[0] | (p[1] << 8));
		p += 2;
		caplen -= 2;
		hdrlen += 2;
		break;

	case 3:
		if (caplen < 2) {
			(*ndo->ndo_printf)(ndo, "[|802.15.4]");
			return 3;
		}
		destpanid = p[0] | (p[1] << 8);
		p += 2;
		caplen -= 2;
		hdrlen += 2;
		if (caplen < 8) {
			(*ndo->ndo_printf)(ndo, "[|802.15.4]");
			return 5;
		}
		if (ndo->ndo_vflag)
			(*ndo->ndo_printf)(ndo, "%04x:%s ", destpanid,
			    le64addr_string(ndo, p));
		p += 8;
		caplen -= 8;
		hdrlen += 8;
		break;
	}

	if (ndo->ndo_vflag)
		(*ndo->ndo_printf)(ndo, "< ");

	switch ((fc >> 14) & 0x3) {

	case 0:
		if (ndo->ndo_vflag)
			(*ndo->ndo_printf)(ndo, "none ");
		break;

	case 1:
		if (ndo->ndo_vflag)
			(*ndo->ndo_printf)(ndo, "reserved source "
			    "addressing mode");
		return 0;

	case 2:
		if (!(fc & 0x40)) {
			if (caplen < 2) {
				(*ndo->ndo_printf)(ndo, "[|802.15.4]");
				return hdrlen;
			}
			destpanid = p[0] | (p[1] << 8);
			p += 2;
			caplen -= 2;
			hdrlen += 2;
		}
		if (caplen < 2) {
			(*ndo->ndo_printf)(ndo, "[|802.15.4]");
			return hdrlen;
		}
		if (ndo->ndo_vflag)
			(*ndo->ndo_printf)(ndo, "%04x:%04x ", destpanid,
			    p[0] | (p[1] << 8));
		p += 2;
		caplen -= 2;
		hdrlen += 2;
		break;

	case 3:
		if (!(fc & 0x40)) {
			if (caplen < 2) {
				(*ndo->ndo_printf)(ndo, "[|802.15.4]");
				return hdrlen;
			}
			destpanid = p[0] | (p[1] << 8);
			p += 2;
			caplen -= 2;
			hdrlen += 2;
		}
		if (caplen < 8) {
			(*ndo->ndo_printf)(ndo, "[|802.15.4]");
			return hdrlen;
		}
		if (ndo->ndo_vflag)
			(*ndo->ndo_printf)(ndo, "%04x:%s ", destpanid,
			    le64addr_string(ndo, p));
		p += 8;
		caplen -= 8;
		hdrlen += 8;
		break;
	}

	if (!ndo->ndo_suppress_default_print)
		(*ndo->ndo_default_print)(ndo, p, caplen);

	return (hdrlen);
}