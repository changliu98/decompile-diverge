int decode_multicast_vpn(netdissect_options *ndo, u_char *packet_ptr, char *buf, u_int buflen)
{
    // Extract the Route Type from the first byte of the packet pointer
    uint8_t rt_type = packet_ptr[0];
    // Extract the Source-Group length from the second byte
    uint8_t source_group_length = packet_ptr[1];
    // Pointer to the Route Distinguisher (RD) field, starting 2 bytes after pptr
    u_char *rd_ptr = packet_ptr + 2;
    int total_length;

    // Check if the remaining buffer space is sufficient for the minimum header size (2 bytes)
    // Note: The condition logic here appears to be checking for underflow/overflow relative to snapend
    if ((ndo->ndo_snapend < ndo->ndo_snapend + -2) || (ndo->ndo_snapend + -2 < packet_ptr)) {
        return -2;
    }

    // Format the initial part of the output string with Route Type and SG Length
    snprintf(buf, buflen, "Route-Type: %s (%u), length: %u",
             tok2str(bgp_multicast_vpn_route_type_values, "Unknown", (uint)rt_type),
             (ulong)rt_type, (ulong)source_group_length);

    // Process based on the specific Route Type
    switch (rt_type) {
    case 1:
        // Check if there is enough data for RD (8 bytes) and Originator IP
        if ((ndo->ndo_snapend < ndo->ndo_snapend + -8) || (ndo->ndo_snapend + -8 < rd_ptr))
            return -2;
        // Append RD and Originator IP to the buffer
        snprintf(buf + strlen(buf), buflen - strlen(buf), ", RD: %s, Originator %s",
                 bgp_vpn_rd_print(ndo, rd_ptr),
                 bgp_vpn_ip_print(ndo, packet_ptr + 10, (source_group_length - 8) * 8));
        break;
    case 2:
        // Check if there is enough data for RD (8 bytes) and Source-AS (4 bytes)
        if ((ndo->ndo_snapend < ndo->ndo_snapend + -0xc) || (ndo->ndo_snapend + -0xc < rd_ptr))
            return -2;
        // Append RD and Source-AS to the buffer
        snprintf(buf + strlen(buf), buflen - strlen(buf), ", RD: %s, Source-AS %s",
                 bgp_vpn_rd_print(ndo, rd_ptr),
                 as_printf(ndo, astostr, 0x14, EXTRACT_32BITS(packet_ptr + 10)));
        break;
    case 3:
        // Complex check for Route Type 3 (Multicast Source-Group with RD and Originator)
        if ((ndo->ndo_snapend + -8 <= ndo->ndo_snapend) && (rd_ptr <= ndo->ndo_snapend + -8)) {
            size_t buf_len = strlen(buf);
            // Append RD to the buffer
            snprintf(buf + buf_len, buflen - buf_len, ", RD: %s", bgp_vpn_rd_print(ndo, rd_ptr));
            // Move pointer to Source-Group data
            rd_ptr = packet_ptr + 10;
            // Print Source-Group information
            int sg_printed_len = bgp_vpn_sg_print(ndo, rd_ptr, buf, buflen);
            // Calculate remaining bytes after Source-Group
            uint8_t originator_len = source_group_length - (char)sg_printed_len;
            // Check if remaining data is valid for Originator IP
            if ((ndo->ndo_snapend + -(ulong)originator_len <= ndo->ndo_snapend) &&
                (rd_ptr <= ndo->ndo_snapend + -(ulong)originator_len)) {
                // Append Originator IP to the buffer
                snprintf(buf + strlen(buf), buflen - strlen(buf), ", Originator %s",
                         bgp_vpn_ip_print(ndo, rd_ptr, originator_len << 3));
                break;
            }
        }
        // Return error if checks fail
        return -2;
    case 4:
        // Route Type 4: No additional fields to print
        break;
    case 5:
        // Check if there is enough data for RD (8 bytes)
        if ((ndo->ndo_snapend < ndo->ndo_snapend + -8) || (ndo->ndo_snapend + -8 < rd_ptr))
            return -2;
        // Append RD to the buffer
        snprintf(buf + strlen(buf), buflen - strlen(buf), ", RD: %s", bgp_vpn_rd_print(ndo, rd_ptr));
        // Print Source-Group information
        bgp_vpn_sg_print(ndo, packet_ptr + 10, buf, buflen);
        break;
    case 6:
    case 7:
        // Check if there is enough data for RD (8 bytes) and Source-AS (4 bytes)
        if ((ndo->ndo_snapend < ndo->ndo_snapend + -8) || (ndo->ndo_snapend + -8 < rd_ptr))
            return -2;
        // Append RD and Source-AS to the buffer
        snprintf(buf + strlen(buf), buflen - strlen(buf), ", RD: %s, Source-AS %s",
                 bgp_vpn_rd_print(ndo, rd_ptr),
                 as_printf(ndo, astostr, 0x14, EXTRACT_32BITS(packet_ptr + 10)));
        // Print Source-Group information
        bgp_vpn_sg_print(ndo, packet_ptr + 10, buf, buflen);
        break;
    }
    // Calculate total length consumed: header (2 bytes) + source-group length
    total_length = source_group_length + 2;
    // Return the total length of the decoded route
    return total_length;
}