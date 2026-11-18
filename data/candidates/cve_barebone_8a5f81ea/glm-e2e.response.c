int pktap_if_print(struct netdissect_options *ndo, const struct pcap_pkthdr *h, const uint8_t *p) {
    uint32_t caplen = h->caplen;
    uint32_t length = h->len;
    uint32_t ret_val;

    if (caplen < 0x6c || length < 0x6c) {
        ndo->error(ndo, "pktap_if_print: length too small");
        ret_val = 0;
        goto end;
    }

    const struct pktap_header *hdr = (const struct pktap_header *)p;
    
    // Big-endian loads
    uint32_t dlt_len = ((uint32_t)p[0x0b] << 24) | ((uint32_t)p[0x0a] << 16) | ((uint32_t)p[0x09] << 8) | p[0x08];
    uint32_t pkt_len = ((uint32_t)p[0x03] << 24) | ((uint32_t)p[0x02] << 16) | ((uint32_t)p[0x01] << 8) | p[0x00];

    if (pkt_len < 0x6c) {
        ndo->error(ndo, "pktap_if_print: length too small");
        ret_val = 0;
        goto end;
    }

    if (caplen < pkt_len || length < pkt_len) {
        ndo->error(ndo, "pktap_if_print: length too small");
        ret_val = pkt_len;
        goto end;
    }

    if (ndo->flag != 0) {
        pktap_header_print(ndo, p, length);
    }

    length -= pkt_len;
    caplen -= pkt_len;
    p += pkt_len;

    uint32_t dlt = hdr->dlt;
    if (dlt == 0) {
        ndo->error(ndo, "pktap_if_print: unknown DLT");
    } else if (dlt == 1) {
        void (*printer)(struct netdissect_options *, const struct pcap_pkthdr *, const uint8_t *) = 
            (void (*)(struct netdissect_options *, const struct pcap_pkthdr *, const uint8_t *))lookup_printer(dlt);
        
        if (printer != NULL) {
            pkt_len += printer(ndo, h, p);
        } else {
            if (ndo->flag == 0) {
                pktap_header_print(ndo, (const uint8_t *)hdr, length + pkt_len);
            }
            if (ndo->flag2 == 0) {
                ndo->default_print(ndo, p, caplen);
            }
        }
    }

    ret_val = pkt_len;

end:
    return ret_val;
}