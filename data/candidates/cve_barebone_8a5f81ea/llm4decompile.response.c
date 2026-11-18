u_int
pktap_if_print(netdissect_options *ndo, const struct pcap_pkthdr *h, const u_char *p)
{
	u_int length = h->len;
	u_int caplen = h->caplen;
	u_int hdrlen;
	u_int dlt;
	u_int rectype;
	if_printer printer;

	if (caplen < sizeof(struct pktap_header) || length < sizeof(struct pktap_header)) {
		ndo->ndo_printf(ndo, "[|pktap]");
		return (0);
	}

	hdrlen = ((((u_int32_t)(p)[0]) << 24) | (((u_int32_t)(p)[1]) << 16) | (((u_int32_t)(p)[2]) << 8) | ((u_int32_t)(p)[3]));
	if (hdrlen < sizeof(struct pktap_header)) {
		ndo->ndo_printf(ndo, "[|pktap]");
		return (0);
	}
	if (caplen < hdrlen || length < hdrlen) {
		ndo->ndo_printf(ndo, "[|pktap]");
		return (hdrlen);
	}

	if (ndo->ndo_eflag)
		pktap_header_print(ndo, p, length);

	rectype = ((((u_int32_t)(p + sizeof(struct pktap_header))[0]) << 24) | (((u_int32_t)(p + sizeof(struct pktap_header))[1]) << 16) | (((u_int32_t)(p + sizeof(struct pktap_header))[2]) << 8) | ((u_int32_t)(p + sizeof(struct pktap_header))[3]));
	if (rectype == 0) {
		ndo->ndo_printf(ndo, "no data");
		return (hdrlen);
	}

	if (rectype != 1)
		return (hdrlen);

	dlt = ((((u_int32_t)(p + sizeof(struct pktap_header) + 4)[0]) << 24) | (((u_int32_t)(p + sizeof(struct pktap_header) + 4)[1]) << 16) | (((u_int32_t)(p + sizeof(struct pktap_header) + 4)[2]) << 8) | ((u_int32_t)(p + sizeof(struct pktap_header) + 4)[3]));
	printer = lookup_printer(dlt);
	if (printer == NULL) {
		if (!ndo->ndo_eflag)
			pktap_header_print(ndo, p, length);
		if (!ndo->ndo_suppress_default_print)
			ndo->ndo_default_print(ndo, p + hdrlen, caplen - hdrlen);
	} else {
		hdrlen += printer(ndo, h, p + hdrlen);
	}

	return (hdrlen);
}