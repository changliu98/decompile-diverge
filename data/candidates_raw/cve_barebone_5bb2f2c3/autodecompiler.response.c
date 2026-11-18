static void scan_openvpn(ndpi_detection_t *ndpi, struct ndpi_flow_info *flow) {
  struct ndpi_packet_info *packet = &flow->packet;
  unsigned char *ovpn_payload = packet->payload;
  u_int16_t ovpn_opcode;
  char failed = 0;

  if(packet->payload_packet_len < 40)
    return;

  if(packet->tcp_reordering) {
    ovpn_payload += 2;
  }

  ovpn_opcode = ovpn_payload[0] & 0xf8;

  if(packet->udp) {

    if(flow->detected_protocol_stack[0] == 1) {

      if((packet->payload_packet_len == 112 && (ovpn_opcode == 0xa8 || ovpn_opcode == 0xc0)) ||
         (packet->payload_packet_len == 80 && (ovpn_opcode == 0xb8 || ovpn_opcode == 0x58 || ovpn_opcode == 0xa0 || ovpn_opcode == 0xa8 || ovpn_opcode == 0xc8))) {
        ndpi_set_detected_protocol(ndpi, flow, 159, 0);
        return;
      }
    }
  } else {

    if(flow->detected_protocol_stack[9] < 5) {

      if(ovpn_opcode == 0x08 || ovpn_opcode == 0x38) {
        char hmac_size = check_pkid_and_detect_hmac_size(ovpn_payload);

        if(hmac_size > 0) {
          flow->openvpn_hmac_size = ovpn_payload[1];
        }
      }
    } else if(flow->detected_protocol_stack[9] >= 1 && flow->detected_protocol_stack[9] <= 5) {

      if(ovpn_opcode == 0x10 || ovpn_opcode == 0x40) {
        char hmac_size = check_pkid_and_detect_hmac_size(ovpn_payload);
        unsigned char session_id_size;

        if(hmac_size > 0) {
          session_id_size = ovpn_payload[9 + hmac_size + 8];

          if(session_id_size > 0) {
            unsigned char *session_remote = &ovpn_payload[9 + hmac_size + 8 + 1 + session_id_size];

            if(!((unsigned long)(flow->openvpn_session_id - *(u_int32_t *)session_remote) != 0)) {
              ndpi_set_detected_protocol(ndpi, flow, 159, 0);
              return;
            } else {
              failed = 1;
            }
          } else {
            failed = 1;
          }
        } else {
          failed = 1;
        }
      }
    } else {
      failed = 1;
    }
  }

  flow->detected_protocol_stack[9]++;

  if(failed) return;
}