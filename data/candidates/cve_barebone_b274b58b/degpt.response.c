u_int print_mfr_protocol(netdissect_options *nd_opts, u_char *packet_ptr, u_int packet_len)
{
    u_int bytes_consumed;
    u_char *ie_ptr;
    u_int ie_remaining_len;
    u_int char_idx;
    uint8_t ie_length;
    uint8_t ie_identifier;
    uint16_t fragment_seq;
    u_int header_length;
    u_int temp_len;
    u_char *temp_packet_ptr;
    netdissect_options *temp_nd_opts;
    u_int temp_bytes_consumed;

    // Check if the packet buffer has enough space for at least 4 bytes
    // If not, print error message and return length
    if ((nd_opts->ndo_snapend < nd_opts->ndo_snapend + -4) || (nd_opts->ndo_snapend + -4 < packet_ptr)) {
LAB_00101d0a:
        (*nd_opts->ndo_printf)(nd_opts, "[|mfr]");
        bytes_consumed = packet_len;
    }
    // Check if this is an FRF.16 Control message (high bits 0xe0 and second byte 0)
    else if (((*packet_ptr & 0xe0) == 0xe0) && (packet_ptr[1] == '\0')) {
        char *flag_str;
        char *msg_type_str;
        uint32_t uint32_val;
        timeval *ie_data_ptr;
        byte ie_type_byte;
        byte ie_len_byte;

        // Decode flags using bit-to-string conversion
        flag_str = bittok2str(frf_flag_values, "none", *packet_ptr & 0xe0);
        // Decode message type using token-to-string conversion
        msg_type_str = tok2str(mfr_ctrl_msg_values, "Unknown Message (0x%02x)", (uint)packet_ptr[2]);
        // Print control message header information
        (*nd_opts->ndo_printf)(nd_opts, "FRF.16 Control, Flags [%s], %s, length %u", flag_str, msg_type_str, (ulong)packet_len);
        
        // Move pointer to start of Information Elements (IEs)
        ie_ptr = packet_ptr + 3;
        // Calculate remaining length for IEs
        ie_remaining_len = packet_len - 3;
        
        // If verbose flag is not set, just return header length
        if (nd_opts->ndo_vflag == 0) {
            bytes_consumed = 3;
        }
        else {
            // Iterate through each Information Element
            for (; 2 < ie_remaining_len; ie_remaining_len = (ie_remaining_len - 2) - (uint)ie_len_byte) {
                // Check bounds before reading IE type and length
                if ((nd_opts->ndo_snapend < nd_opts->ndo_snapend + -2) || (nd_opts->ndo_snapend + -2 < ie_ptr))
                    goto LAB_00101d0a;
                
                // Read IE type and length
                ie_type_byte = *ie_ptr;
                ie_len_byte = ie_ptr[1];
                
                // Decode IE type
                flag_str = tok2str(mfr_ctrl_ie_values, "Unknown", (uint)ie_type_byte);
                // Print IE header
                (*nd_opts->ndo_printf)(nd_opts, "\n\tIE %s (%u), length %u: ", flag_str, (ulong)ie_type_byte, (ulong)ie_len_byte);
                
                // Validate IE: type must not be 0 and length must be at least 3
                if ((ie_type_byte == 0) || (ie_len_byte < 3)) {
                    return 3;
                }
                
                // Check bounds for IE data
                if ((nd_opts->ndo_snapend < nd_opts->ndo_snapend + -(ulong)ie_len_byte) ||
                    (nd_opts->ndo_snapend + -(ulong)ie_len_byte < ie_ptr)) 
                    goto LAB_00101d0a;
                
                // Point to IE data (skip type and length bytes)
                ie_data_ptr = (timeval *)(ie_ptr + 2);
                // Adjust length to exclude type and length bytes
                ie_len_byte = ie_len_byte - 2;
                
                // Process IE based on its type
                switch(ie_type_byte) {
                case 1:
                case 2:
                    // Print string data character by character until null terminator or max length
                    for (char_idx = 0; (char_idx < ie_len_byte && char_idx < 0x32 &&
                                  (*(char *)((long)&ie_data_ptr->tv_sec + (ulong)char_idx) != '\0')); char_idx = char_idx + 1) {
                        safeputchar(nd_opts, *(u_char *)((long)&ie_data_ptr->tv_sec + (ulong)char_idx));
                    }
                    break;
                case 3:
                    // Print 32-bit unsigned integer in hexadecimal
                    uint32_val = EXTRACT_32BITS(ie_data_ptr);
                    (*nd_opts->ndo_printf)(nd_opts, "0x%08x", (ulong)uint32_val);
                    break;
                case 5:
                    // Print timestamp if length is exactly 16 bytes
                    if (ie_len_byte != 0x10) 
                        goto switchD_00101a47_caseD_6;
                    ts_print(nd_opts, ie_data_ptr);
                    break;
                case 6:
                case 7:
switchD_00101a47_caseD_6:
                default:
                    // Print unknown data if verbose level is less than 2
                    if (nd_opts->ndo_vflag < 2) {
                        print_unknown_data(nd_opts, (u_char *)ie_data_ptr, "\n\t  ", (uint)ie_len_byte);
                    }
                }
                
                // If verbose level is greater than 1, always print unknown data
                if (1 < nd_opts->ndo_vflag) {
                    print_unknown_data(nd_opts, (u_char *)ie_data_ptr, "\n\t  ", (uint)ie_len_byte);
                }
                
                // Move pointer to next IE
                ie_ptr = (uint8_t *)((long)&ie_data_ptr->tv_sec + (long)(int)(uint)ie_len_byte);
            }
            bytes_consumed = 3;
        }
    }
    else {
        uint16_t seq_num_val;
        char *flag_str;

        // Extract sequence number from first two bytes
        seq_num_val = (*packet_ptr & 0x1e) << 7 | (ushort)packet_ptr[1];
        
        // Check if this is a fragmented message (high bits 0xc0 or 0x80)
        if (((*packet_ptr & 0xe0) == 0xc0) || ((*packet_ptr & 0xe0) == 0x80)) {
            // Decode flags
            flag_str = bittok2str(frf_flag_values, "none", *packet_ptr & 0xe0);
            // Print fragment header and recursively print FR data
            (*nd_opts->ndo_printf)(nd_opts, "FRF.16 Frag, seq %u, Flags [%s], ", (ulong)seq_num_val, flag_str);
            fr_print(nd_opts, packet_ptr + 2, packet_len - 2);
            bytes_consumed = 2;
        }
        else {
            // Decode flags for non-fragmented or other cases
            flag_str = bittok2str(frf_flag_values, "none", *packet_ptr & 0xe0);
            // Print fragment header
            (*nd_opts->ndo_printf)(nd_opts, "FRF.16 Frag, seq %u, Flags [%s]", (ulong)seq_num_val, flag_str);
            // Print remaining unknown data
            print_unknown_data(nd_opts, packet_ptr, "\n\t", packet_len);
            bytes_consumed = 0;
        }
    }
    return bytes_consumed;
}