u_int __cdecl pktap_if_print(netdissect_options *ndo, const struct pcap_pkthdr *h, const u_char *p)
{
    bpf_u_int32 caplen = h->caplen;
    bpf_u_int32 length = h->len;

    // PKTAP_MIN_HEADER_SIZE is 0x6C (108 bytes)
    if (caplen < 0x6C || length < 0x6C)
        goto trunc;

    // Read 32-bit little-endian fields directly from the packet buffer
    uint32_t dlt    = (uint32_t)p[8]  | ((uint32_t)p[9]  << 8) | ((uint32_t)p[10] << 16) | ((uint32_t)p[11] << 24);
    uint32_t hdrlen = (uint32_t)p[0]  | ((uint32_t)p[1]  << 8) | ((uint32_t)p[2]  << 16) | ((uint32_t)p[3]  << 24);

    if (hdrlen < 0x6C)
        goto trunc;

    if (caplen < hdrlen || length < hdrlen)
        goto trunc;

    if (ndo->ndo_eflag)
        pktap_header_print(ndo, p, length);

    const u_char *pb = p + hdrlen;
    u_int caplena = caplen - hdrlen;
    u_int lengtha = length - hdrlen;

    // p[4..7] represents the interface type or packet family
    uint32_t pkt_type = *(const uint32_t *)(p + 4);

    if (pkt_type == 0)
    {
        ndo->ndo_printf(ndo, "no data");
    }
    else if (pkt_type == 1)
    {
        if_printer printer = lookup_printer(dlt);
        if (printer)
        {
            hdrlen += printer(ndo, h, pb);
        }
        else
        {
            if (!ndo->ndo_eflag)
                pktap_header_print(ndo, p, hdrlen + lengtha);
            if (!ndo->ndo_suppress_default_print)
                ndo->ndo_default_print(ndo, pb, caplena);
        }
    }

    return hdrlen;

trunc:
    ndo->ndo_printf(ndo, "[|pktap]");
    return (caplen < 0x6C || length < 0x6C || hdrlen < 0x6C) ? 0 : hdrlen;
}