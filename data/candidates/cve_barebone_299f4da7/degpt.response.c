void handle_mlppp(netdissect_options *nd_opts, u_char *packet_ptr, int pkt_len)
{
    // If extended flag is not set, print the MLPPP label
    if (nd_opts->ndo_eflag == 0) {
        (*nd_opts->ndo_printf)(nd_opts, "MLPPP, ");
    }
    // Print sequence number (lower 12 bits of first 16-bit field), flags, and total length
    (*nd_opts->ndo_printf)(nd_opts, "seq 0x%03x, Flags [%s], length %u",
                       extract_16bits(packet_ptr) & 0xfff,
                       bittok2str(mlppp_flag_strings, "none", *packet_ptr & 0xc0),
                       (uint)pkt_len);
}