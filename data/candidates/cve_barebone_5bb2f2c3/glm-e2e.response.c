void ndpi_search_openvpn(struct ndpi_detection_module_struct *ndpi_struct, 
                         struct ndpi_flow_struct *flow) {
    const uint8_t *payload = flow->packet_payload;
    const uint8_t *packet_end = flow->packet_payload_end;
    uint8_t invalid_byte = 0;
    int8_t hmac_size = 0;
    uint8_t opcode = 0;
    uint8_t tls_type = 0;
    const uint8_t *tls_payload = NULL;

    // Check if the packet length is at least 40 bytes
    if (flow->packet_len < 0x28) {
        return;
    }

    // Skip the 2-byte packet ID if present
    if (flow->has_packet_id != 0) {
        payload += 2;
    }

    // Extract the 5 most significant bits of the opcode
    opcode = *payload & 0xF8;

    // Check if it's a TCP packet
    if (flow->l4_proto != 0) {
        if (flow->packet_len == 0x70) {
            if (opcode == 0xA8 || opcode == 0xC0) {
                ndpi_set_detected_protocol(ndpi_struct, flow, 0x9F, 0);
                return;
            }
        } else if (flow->packet_len == 0x50) {
            if (opcode == 0xB8 || opcode == 0x58 || opcode == 0xA0 || 
                opcode == 0xA8 || opcode == 0xC8) {
                ndpi_set_detected_protocol(ndpi_struct, flow, 0x9F, 0);
                return;
            }
        }
    } else {
        // UDP packet checks
        if (flow->packet_counter < 5) {
            if (opcode == 0x08 || opcode == 0x38) {
                hmac_size = check_pkid_and_detect_hmac_size(payload);
                if (hmac_size > 0) {
                    flow->packet_id = *(payload + 1);
                }
            }
        } else if (flow->packet_counter >= 1 && flow->packet_counter <= 5) {
            if (opcode == 0x10 || opcode == 0x40) {
                hmac_size = check_pkid_and_detect_hmac_size(payload);
                if (hmac_size > 0) {
                    tls_type = payload[hmac_size + 9 + 8];
                    if (tls_type > 0) {
                        tls_payload = payload + hmac_size + 9 + 8 + 1 + (tls_type << 2);
                        if (*(flow->packet_id_ptr) - *tls_payload == 0) {
                            ndpi_set_detected_protocol(ndpi_struct, flow, 0x9F, 0);
                            return;
                        } else {
                            invalid_byte = 1;
                        }
                    } else {
                        invalid_byte = 1;
                    }
                } else {
                    invalid_byte = 1;
                }
            } else {
                invalid_byte = 1;
            }
        } else {
            invalid_byte = 1;
        }
    }

    // Increment packet counter
    flow->packet_counter++;

    // The following condition evaluates to true if invalid_byte is 1, 
    // or if it is 0 (due to the bitwise OR with 0). It essentially does nothing 
    // but was explicitly generated in the assembly block.
    if (invalid_byte != 0 || invalid_byte == 0) {
        // do nothing
    }
}