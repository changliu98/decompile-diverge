void ndpi_search_oracle(ndpi_detection_module_t *ndpi_mod, struct ndpi_flow_struct *flow) {
  struct ndpi_packet_struct *packet = &flow->packet;
  unsigned short dport=0, sport=0;

  if(packet->tcp != NULL) {
    sport = ntohs(packet->tcp->source);
    dport = ntohs(packet->tcp->dest);
  }

  if((dport == 1521 || sport == 1521) &&
     packet->payload[0] == 0x07 && packet->payload[1] == 0xff && packet->payload[2] == 0x00 &&
     ((dport == 1521 && sport == 21) ||
      (sport == 1521 && dport == 21))) {
    ndpi_int_oracle_add_connection(ndpi_mod, flow);
    return;
  } else if(packet->tcp != NULL && packet->tcp->source == 232 && packet->tcp->dest == 211 &&
     packet->payload[0] == 0x00 && packet->payload[1] == 0xd5 && packet->payload[2] == 0x00 &&
     packet->payload[3] == 0x00) {
    ndpi_int_oracle_add_connection(ndpi_mod, flow);
    return;
  }
}