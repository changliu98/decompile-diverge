u_int chdlc_if_print(netdissect_options *net_dissect_opts, pcap_pkthdr *packet_header, u_char *packet_data)
{
    // Check if the captured packet length is less than the minimum CHDLC header size (4 bytes)
    if (packet_header->caplen < 4) {
        // Print an error message indicating an incomplete CHDLC packet
        (*net_dissect_opts->ndo_printf)(net_dissect_opts, "[|chdlc]");
        return 0;
    }
    // Delegate to the main CHDLC print function to decode and display the packet
    return chdlc_print(net_dissect_opts, packet_data, packet_header->len);
}