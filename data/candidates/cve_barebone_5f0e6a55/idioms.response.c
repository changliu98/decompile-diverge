int ieee802_15_4_if_print(struct netdissect_options *ndo, struct pcap_pkthdr *phdr, unsigned char *data)
{
    unsigned int caplen = phdr->caplen;
    unsigned int offset;
    unsigned char *p;
    unsigned short fc;
    unsigned char seq;
    unsigned short panid = 0;
    int len;
    if (caplen < 3) {
        ndo->ndo_printf(ndo, "[|802.15.4]");
        return (caplen);
    }
    len = 3;
    p = data;
    fc = p[0] & 0xff;
    seq = p[2];
    p += 3;
    caplen -= 3;
    ndo->ndo_printf(ndo, "IEEE 802.15.4 %s packet ",
      ftypes[fc & 0x07]);
    if (ndo->ndo_vflag)
        ndo->ndo_printf(ndo, "seq %02x ", seq);
    switch (fc & 0x0c >> 2) {
    case 0:
        if (fc & 0x40)
            goto no_addr;
        if (ndo->ndo_vflag)
            ndo->ndo_printf(ndo, "none ");
        break;
    case 1:
        if (ndo->ndo_vflag)
            ndo->ndo_printf(ndo, "reserved destination addressing mode");
        return (3);
    case 2:
        if (caplen < 2)
            goto no_addr;
        panid = p[0] & 0xff;
        panid |= (p[1] & 0xff) << 8;
        p += 2;
        caplen -= 2;
        len += 2;
        if (caplen < 2)
            goto no_addr;
        if (ndo->ndo_vflag)
            ndo->ndo_printf(ndo, "%04x:%04x ", panid,
              (p[0] & 0xff) | ((p[1] & 0xff) << 8));
        p += 2;
        caplen -= 2;
        len += 2;
        goto no_addr;
    case 3:
        if (caplen < 2 || caplen < 8)
            goto no_addr;
        if (ndo->ndo_vflag) {
            int (*printf)(struct netdissect_options *, char *, ...);
            printf = ndo->ndo_printf;
            printf(ndo, "%04x:%s ", panid,
      ieee802154_ntoa(ndo, p));
        }
        p += 2;
        caplen -= 2;
        len += 2;
        p += 6;
        caplen -= 6;
        len += 6;
        goto no_addr;
    }
no_addr:
    if (ndo->ndo_vflag)
        ndo->ndo_printf(ndo, "< ");
    switch (fc & 0xf0 >> 4) {
    case 0:
        if (ndo->ndo_vflag)
            ndo->ndo_printf(ndo, "none ");
        break;
    case 1:
        if (ndo->ndo_vflag)
            ndo->ndo_printf(ndo, "reserved source addressing mode");
        return (0);
    case 2:
        if (fc & 0x40)
            goto addr1;
        if (caplen < 2)
            goto no_addr;
        panid = p[0] & 0xff;
        panid |= (p[1] & 0xff) << 8;
        p += 2;
        caplen -= 2;
        len += 2;
    addr1:
        if (caplen < 2)
            goto no_addr;
        if (ndo->ndo_vflag)
            ndo->ndo_printf(ndo, "%04x:%04x ", panid,
              (p[0] & 0xff) | ((p[1] & 0xff) << 8));
        p += 2;
        caplen -= 2;
        len += 2;
        break;
    case 3:
        if (fc & 0x40)
            goto addr2;
        if (caplen < 2)
            goto no_addr;
        panid = p[0] & 0xff;
        panid |= (p[1] & 0xff) << 8;
        p += 2;
        caplen -= 2;
        len += 2;
    addr2:
        if (caplen < 8)
            goto no_addr;
        if (ndo->ndo_vflag) {
            int (*printf)(struct netdissect_options *, char *, ...);
            printf = ndo->ndo_printf;
            printf(ndo, "%04x:%s ", panid,
      ieee802154_ntoa(ndo, p));
        }
        p += 8;
        caplen -= 8;
        len += 8;
        break;
    }
    if (!ndo->ndo_suppress_default_print)
        ndo->ndo_default_print(ndo, p, caplen);
    offset = len;
    return (offset);
}