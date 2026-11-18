void ndpi_search_oracle(struct ndpi_flow_struct *flow, struct ndpi_packet_struct *packet) {
    unsigned short source_port = 0;
    unsigned short dest_port = 0;

    if (packet->payload == NULL) {
        return;
    }

    // Note: The assembly dereferences the payload pointer to read ports.
    // This implies the payload starts with an IP/UDP header or similar structure.
    source_port = ntohs(*(unsigned short *)(packet->payload));
    dest_port = ntohs(*(unsigned short *)(packet->payload + 2));

    if (dest_port == 1521 || source_port == 1521) {
        if (packet->payload[0] == 0x07 && 
            packet->payload[1] == 0xFF && 
            packet->payload[2] == 0x00) {
            ndpi_int_oracle_add_connection(flow, packet);
        } else if (packet->payload_len >= 232) {
            if ((packet->payload[0] == 0x00 || packet->payload[0] == 0x01) &&
                packet->payload[1] != 0x00 &&
                packet->payload[2] == 0x00 &&
                packet->payload[3] == 0x00) {
                ndpi_int_oracle_add_connection(flow, packet);
            }
        }
    } else if (packet->payload_len == 213) {
        if (packet->payload[0] == 0x00 && 
            packet->payload[1] == 0xD5 && 
            packet->payload[2] == 0x00 && 
            packet->payload[3] == 0x00) {
            ndpi_int_oracle_add_connection(flow, packet);
        }
    }
}