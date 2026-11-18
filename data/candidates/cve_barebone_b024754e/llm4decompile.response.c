void ndpi_search_oracle(ndpi_detection_module_struct *ndpi_struct, ndpi_flow_struct *flow) {
  if (flow->packet.tcp != NULL) {
    uint16_t sport = ntohs(flow->packet.tcp->source);
    uint16_t dport = ntohs(flow->packet.tcp->dest);

    if ((dport == 1521 || sport == 1521)
        && (((flow->packet.payload[0] == 0x07 && flow->packet.payload[1] == 0xFF && flow->packet.payload[2] == 0x00)
            || (flow->packet.payload_packet_len >= 232 && (flow->packet.payload[0] == 0x00 || flow->packet.payload[0] == 0x01)
                && flow->packet.payload[1] != 0x00 && flow->packet.payload[2] == 0x00 && flow->packet.payload[3] == 0x00))) {

      ndpi_int_oracle_add_connection(ndpi_struct, flow);
    } else if (flow->packet.payload_packet_len == 213
               && flow->packet.payload[0] == 0x00 && flow->packet.payload[1] == 0xD5
               && flow->packet.payload[2] == 0x00 && flow->packet.payload[3] == 0x00) {

      ndpi_int_oracle_add_connection(ndpi_struct, flow);
    }
  }
}