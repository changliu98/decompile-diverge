int chdlc_print(struct netdissect_options *ndo, struct pcap_pkthdr *phdr, unsigned char *data)
{
    unsigned int caplen = phdr->caplen;
    if (caplen < sizeof(struct chdlc_hdr)) {
        ndo->ndo_printf(ndo, "[|chdlc]");
        return caplen;
    }
    return chdlc_dissect(ndo, data, phdr->len);
}