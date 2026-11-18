static int chdlc_print(struct netdissect_options *ndo, struct pcap_pkthdr *phdr, unsigned char *pkt)
{
    struct chdlc_header *chdlch;
    unsigned int ethertype;
    int length;
    chdlch = (struct chdlc_header *)(pkt + sizeof(struct chdlc_header));
    ethertype = GET_BE_16((unsigned char *)chdlch);
    if (ndo->ndo_eflag) {
        int (*printf)(struct netdissect_options *, char *, ...);
        printf = ndo->ndo_printf;
        printf(ndo, "%s, ethertype %s (0x%04x), length %u: ",
               chdlc_cast_valstr(ndo, (unsigned char *)chdlch),
               ethertype_valstr(ndo, ethertype),
               ethertype,
               phdr->caplen - sizeof(struct chdlc_header));
    }
    length = phdr->caplen - sizeof(struct chdlc_header);
    pkt += sizeof(struct chdlc_header);
    switch (ethertype) {
    case ETHERTYPE_IP:
        ip_print(ndo, (struct ip *)pkt, length);
        break;
    case ETHERTYPE_ARP:
        arp_print(ndo, (struct arphdr *)pkt, length);
        break;
    case ETHERTYPE_IPV6:
        ip6_print(ndo, (struct ip6_hdr *)pkt, length);
        break;
    case ETHERTYPE_PPPoEDISC:
    case ETHERTYPE_PPPoSESC:
    case ETHERTYPE_PPPoS:
        if (chdlch->chdlc_type == 0x81 ||
            chdlch->chdlc_type == 0x82 ||
            chdlch->chdlc_type == 0x83)
            pppoe_print(ndo, (struct pppoe_hdr *) (pkt + sizeof(struct chdlc_header)),
                        length - sizeof(struct chdlc_header),
                        ndo->ndo_snapend - (unsigned char *)pkt - sizeof(struct chdlc_header));
        else
            pppoe_print(ndo, (struct pppoe_hdr *) (pkt),
                        length,
                        ndo->ndo_snapend - (unsigned char *)pkt);
        break;
    case ETHERTYPE_IPX:
    case ETHERTYPE_ATALK:
    case ETHERTYPE_PRONET:
        if (ndo->ndo_eflag)
            break;
        ndo->ndo_printf(ndo, "unknown CHDLC protocol (0x%04x)", ethertype);
        break;
    default:
        break;
    }
    return (sizeof(struct chdlc_header));
}