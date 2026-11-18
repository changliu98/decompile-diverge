void __cdecl ndpi_search_openvpn(ndpi_detection_module_struct *ndpi_struct, ndpi_flow_struct *flow)
{
  int8_t hmac_size;
  u_int8_t alen;
  u_int8_t opcode;
  const u_int8_t *ovpn_payload;

  ovpn_payload = flow->packet.payload;
  
  if (flow->packet.payload_packet_len < 40) // 0x28
    return;

  if (flow->packet.tcp)
    ovpn_payload += 2;

  // Extract the 5 most significant bits (opcode)
  opcode = *ovpn_payload & 0xF8;

  // Check for specific UDP initial packet patterns
  if (flow->packet.udp && flow->num_processed_pkts == 1)
  {
    if (flow->packet.payload_packet_len == 112 && (opcode == 168 || opcode == 192))
      goto detected;
      
    if (flow->packet.payload_packet_len == 80 && 
        (opcode == 184 || opcode == 88 || opcode == 160 || opcode == 168 || opcode == 200))
      goto detected;
  }

  if (flow->ovpn_counter < 5 && (opcode == 8 || opcode == 56))
  {
    // Initial handshake state
    if (check_pkid_and_detect_hmac_size(ovpn_payload) > 0)
    {
      // Store 8-byte session ID
      *(uint64_t *)flow->ovpn_session_id = *(uint64_t *)(ovpn_payload + 1);
    }
  }
  else if (flow->ovpn_counter > 0 && flow->ovpn_counter <= 5 && (opcode == 16 || opcode == 64))
  {
    // Subsequent handshake state
    hmac_size = check_pkid_and_detect_hmac_size(ovpn_payload);
    if (hmac_size > 0)
    {
      alen = ovpn_payload[hmac_size + 17];
      if (alen != 0)
      {
        // Verify if the 8-byte session ID matches the previously stored one
        if (*(uint64_t *)flow->ovpn_session_id == *(uint64_t *)&ovpn_payload[4 * alen + 18 + hmac_size])
        {
detected:
          ndpi_set_detected_protocol(ndpi_struct, flow, 0x9Fu, 0);
          return;
        }
      }
    }
  }

  flow->ovpn_counter++;
}