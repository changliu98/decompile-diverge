u_int __cdecl chdlc_if_print(netdissect_options *ndo, const pcap_pkthdr *h, const u_char *p)
{
    uint32_t caplen = h->caplen;

    // CHDLC requires a minimum of 4 bytes for its header.
    // If the captured length is sufficient, process the full packet.
    if (caplen >= 4) {
        return chdlc_print(ndo, p, h->len);
    }

    // Otherwise, the packet was truncated during capture.
    // Print a truncation error indicator and return the number of bytes actually captured.
    ndo->ndo_printf(ndo, "[|chdlc]");
    return caplen;
}