void ndpi_search_oracle(struct ndpi_main_instance_ *ndpi,
                        struct ndpi_connection_search_t *packet) {
  if (packet->parsed.tcp == NULL) return;
  if (((ntohs(packet->parsed.tcp->port_src) == 1521) ||
       (ntohs(packet->parsed.tcp->port_dst) == 1521)) &&
      (((packet->parsed.payload[0] == 0x07) &&
        (packet->parsed.payload[1] == 0xff) &&
        (packet->parsed.payload[2] == 0x00)) ||
       ((packet->parsed.payload_packet_size >= 232) &&
        ((packet->parsed.payload[0] == 0x00) ||
         (packet->parsed.payload[0] == 0x01)) &&
        (packet->parsed.payload[1] != 0x00) &&
        (packet->parsed.payload[2] == 0x00) &&
        (packet->parsed.payload[3] == 0x00)) ||
       ((packet->parsed.payload_packet_size == 213) &&
        (packet->parsed.payload[0] == 0x00) &&
        (packet->parsed.payload[1] == 0xd5) &&
        (packet->parsed.payload[2] == 0x00) &&
        (packet->parsed.payload[3] == 0x00)))) {
    ndpi_int_oracle_add_connection(ndpi, packet);
  }
}