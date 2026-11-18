int print_pktap(struct netdissect_options *ndo, struct pcap_pkthdr *phdr, unsigned char *data)
{
    unsigned int caplen = phdr->caplen;
    unsigned int len = phdr->len;
    unsigned int hlen;
    unsigned int dlt;
    unsigned char *nh;
    int (*printfunc)(struct netdissect_options *ndo, struct pcap_pkthdr *phdr, unsigned char *data);
    if (caplen < sizeof(struct pktap_header) ||
        len < sizeof(struct pktap_header)) {
        ndo->ndo_printf(" [|pktap]");
        return 0;
    }
    dlt = (data[8] | (data[9] << 8) | (data[10] << 16) | (data[11] << 24));
    hlen = (data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24));
    if (hlen < sizeof(struct pktap_header)) {
        ndo->ndo_printf(" [|pktap]");
        return 0;
    }
    if (caplen < hlen || len < hlen) {
        ndo->ndo_printf(" [|pktap]");
        return hlen;
    }
    if (ndo->ndo_eflag)
        print_dissect_error(ndo, data, len);
    len -= hlen;
    caplen -= hlen;
    nh = data + hlen;
    switch (data[4]) {
    case 0:
        ndo->ndo_printf("no data");
        break;
    case 1:
        printfunc = get_pktap_printfunc(dlt);
        if (printfunc)
            hlen += printfunc(ndo, phdr, nh);
        else {
            if (!ndo->ndo_eflag)
                print_dissect_error(ndo, data, hlen + len);
            if (!ndo->ndo_suppress_default_print)
                ndo->ndo_default_print(ndo, nh, caplen);
        }
        break;
    default:
        break;
    }
    return hlen;
}