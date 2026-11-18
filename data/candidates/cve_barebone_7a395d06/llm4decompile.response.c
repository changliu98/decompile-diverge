u_int
chdlc_if_print(netdissect_options *ndo, const struct pcap_pkthdr *h, const u_char *p)
{
	u_int length;

	if (h->caplen < 4) {
		(*ndo->ndo_printf)(ndo, "[|chdlc]");
		return (h->caplen);
	}
	length = chdlc_print(ndo, p, h->len);
	return (length);
}