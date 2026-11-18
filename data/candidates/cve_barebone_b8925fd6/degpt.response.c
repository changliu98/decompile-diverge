int ospf6_print_lshdr(netdissect_options *netdissect_ctx, lsa6_hdr *lsa_header, u_char *buffer_end)
{
    // Check if the LSA header extends beyond the available data buffer
    // Check for potential integer underflow/overflow in snapend calculations
    // Check if the LS type field is within the valid data range
    // Check for potential integer underflow/overflow in snapend calculations
    // Check if the LS sequence number field is within the valid data range
    if (buffer_end < lsa_header + 1 ||
        netdissect_ctx->ndo_snapend < netdissect_ctx->ndo_snapend - 2 ||
        netdissect_ctx->ndo_snapend - 2 < &lsa_header->ls_type ||
        netdissect_ctx->ndo_snapend < netdissect_ctx->ndo_snapend - 4 ||
        netdissect_ctx->ndo_snapend - 4 < &lsa_header->ls_seq) {
        return 1;
    }

    // Convert the advertising router's IPv6 address to a string representation
    char *router_addr_str = ipaddr_string(netdissect_ctx, &lsa_header->ls_router);
    // Extract the 32-bit LS sequence number from the header
    uint32_t ls_sequence_number = EXTRACT_32BITS(&lsa_header->ls_seq);
    // Extract the 16-bit LS age from the header (assuming offset 0)
    uint16_t ls_age = EXTRACT_16BITS(lsa_header);
    // Extract the 16-bit LS length from the header
    uint16_t ls_length = EXTRACT_16BITS(&lsa_header->ls_length);

    // Print the LSA header details: Advertising Router, Sequence Number, Age, and Length
    // Note: Length printed is the total LSA length minus the header size (0x14 bytes)
    netdissect_ctx->ndo_printf(netdissect_ctx, "\n\t  Advertising Router %s, seq 0x%08x, age %us, length %u",
                    router_addr_str, (ulong)ls_sequence_number, (ulong)ls_age, (ulong)(ls_length - 0x14));

    // Extract the 16-bit LS type from the header
    ls_age = EXTRACT_16BITS(&lsa_header->ls_type);
    // Print the specific LS type information and state ID
    ospf6_print_ls_type(netdissect_ctx, (uint)ls_age, &lsa_header->ls_stateid);

    return 0;
}