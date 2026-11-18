void ndpi_search_openvpn(struct ndpi_detection_module_struct *ndpi_hit,
                         struct ndpi_flow_struct *flow) {
  unsigned char *packet = flow->packet.payload;
  unsigned char first_byte;
  int hmac_size;
  if (flow->packet.payload_packet_len < 40) return;
  if (flow->packet.tcp_packet_len) packet += 2;
  first_byte = packet[0] & 0xf8;
  if (flow->packet.is_v6 && flow->l4_protocol == 1) {
    if ((flow->packet.payload_packet_len == 112 &&
         (first_byte == 0xa8 || first_byte == 0xc0)) ||
        (flow->packet.payload_packet_len == 80 &&
         (first_byte == 0xb8 || first_byte == 0x58 || first_byte == 0xa0 ||
          first_byte == 0xa8 || first_byte == 0xc8))) {
      ndpi_set_detected_protocol(ndpi_hit, flow, 159, 0);
      return;
    }
  }
  if (flow->openvpn_stage < 5 && (first_byte == 0x08 || first_byte == 0x38)) {
    hmac_size = check_pkid_and_detect_hmac_size(packet);
    if (hmac_size > 0) memcpy(flow->openvpn_pkid, packet + 1, 8);
  } else if (flow->openvpn_stage > 0 && flow->openvpn_stage < 6 &&
             (first_byte == 0x10 || first_byte == 0x40)) {
    hmac_size = check_pkid_and_detect_hmac_size(packet);
    if (hmac_size > 0) {
      unsigned char hmac_len = packet[17 + hmac_size];
      if (hmac_len > 0 &&
          flow->openvpn_pkid[0] == packet[18 + hmac_size + hmac_len]) {
        ndpi_set_detected_protocol(ndpi_hit, flow, 159, 0);
        return;
      }
    }
  }
  flow->openvpn_stage++;
}