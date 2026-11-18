__attribute__((used)) static int
chdlc_if_print(netdissect_options *ndo,
               register const struct pcap_pkthdr *h, register u_char *p)
{
	register u_int length = h->len;
	register u_int caplen = h->caplen;
	int             ret;

	if (caplen < sizeof(struct chdlc_header)) {
		(*ndo->ndo_printf)(ndo, "[|chdlc]");
		ret = caplen;
	} else {
		ret = chdlc_print(ndo, p, length);
	}

	return (ret);
}