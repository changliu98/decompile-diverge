void ndpi_search_openvpn(ndpi_detection_module_struct *ndpi_struct, ndpi_flow_struct *flow)
{
  unsigned char *buffer = flow->packet.payload;
  u_int32_t buffer_len = flow->packet.payload_packet_len;
  u_int8_t opcode;






  if(buffer_len < 40)
    return;


  if(flow->packet.tcp != NULL)
    buffer += 2;

  opcode = buffer[0] & 0xF8;


  if(flow->packet.udp != NULL && flow->num_processed_pkts == 1) {






    if((buffer_len == 112 && (opcode == 0xA8 || opcode == 0xC0)) ||
       (buffer_len == 80 && (opcode == 0xB8 || opcode == 0x58 || opcode == 0xA0 || opcode == 0xA8 || opcode == 0xC8))) {
      ndpi_set_detected_protocol(ndpi_struct, flow, 159, 0);
      return;
    }
  }






  if(flow->ovpn_counter < 5 && (opcode == 0x08 || opcode == 0x38)) {
    int8_t hmac_size = check_pkid_and_detect_hmac_size(buffer);

    if(hmac_size > 0) {

      flow->ovpn_session_id[0] = buffer[1];
      flow->ovpn_session_id[1] = buffer[2];
      flow->ovpn_session_id[2] = buffer[3];
      flow->ovpn_session_id[3] = buffer[4];
      flow->ovpn_session_id[4] = buffer[5];
      flow->ovpn_session_id[5] = buffer[6];
      flow->ovpn_session_id[6] = buffer[7];
      flow->ovpn_session_id[7] = buffer[8];
      flow->ovpn_session_id[8] = buffer[9];
      flow->ovpn_session_id[9] = buffer[10];
    }
  } else if(flow->ovpn_counter > 0 && flow->ovpn_counter < 6 && (opcode == 0x10 || opcode == 0x40)) {






    int8_t hmac_size = check_pkid_and_detect_hmac_size(buffer);

    if(hmac_size > 0) {






      u_int8_t session_id_pos = 17 + hmac_size;
      u_int8_t session_id_len = buffer[session_id_pos];

      if(session_id_len > 0) {
 session_id_pos++;
 session_id_len *= 4;






 if(flow->ovpn_session_id[0] == buffer[session_id_pos] &&
    flow->ovpn_session_id[1] == buffer[session_id_pos+1] &&
    flow->ovpn_session_id[2] == buffer[session_id_pos+2] &&
    flow->ovpn_session_id[3] == buffer[session_id_pos+3] &&
    flow->ovpn_session_id[4] == buffer[session_id_pos+4] &&
    flow->ovpn_session_id[5] == buffer[session_id_pos+5] &&
    flow->ovpn_session_id[6] == buffer[session_id_pos+6] &&
    flow->ovpn_session_id[7] == buffer[session_id_pos+7] &&
    flow->ovpn_session_id[8] == buffer[session_id_pos+8] &&
    flow->ovpn_session_id[9] == buffer[session_id_pos+9]) {
   ndpi_set_detected_protocol(ndpi_struct, flow, 159, 0);
   return;
 }
      }
    }
  }

  flow->ovpn_counter++;
}