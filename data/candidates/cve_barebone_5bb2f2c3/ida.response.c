void __cdecl ndpi_search_openvpn(ndpi_detection_module_struct *ndpi_struct, ndpi_flow_struct *flow)
{
  int8_t hmac_size; // [rsp+5h] [rbp-2Bh]
  u_int8_t alen; // [rsp+6h] [rbp-2Ah]
  u_int8_t opcode; // [rsp+7h] [rbp-29h]
  const u_int8_t *ovpn_payload; // [rsp+10h] [rbp-20h]

  ovpn_payload = flow->packet.payload;
  if ( flow->packet.payload_packet_len >= 0x28u )
  {
    if ( flow->packet.tcp )
      ovpn_payload += 2;
    opcode = *ovpn_payload & 0xF8;
    if ( flow->packet.udp
      && flow->num_processed_pkts == 1
      && (flow->packet.payload_packet_len == 112 && (opcode == 168 || opcode == 192)
       || flow->packet.payload_packet_len == 80
       && (opcode == 184 || opcode == 88 || opcode == 160 || opcode == 168 || opcode == 200)) )
    {
      goto LABEL_29;
    }
    if ( flow->ovpn_counter < 5u && (opcode == 8 || opcode == 56) )
    {
      if ( check_pkid_and_detect_hmac_size(ovpn_payload) > 0 )
        *(_QWORD *)flow->ovpn_session_id = *(_QWORD *)(ovpn_payload + 1);
    }
    else if ( flow->ovpn_counter && flow->ovpn_counter <= 5u && (opcode == 16 || opcode == 64) )
    {
      hmac_size = check_pkid_and_detect_hmac_size(ovpn_payload);
      if ( hmac_size > 0 )
      {
        alen = ovpn_payload[hmac_size + 17];
        if ( alen )
        {
          if ( *(_QWORD *)flow->ovpn_session_id == *(_QWORD *)&ovpn_payload[4 * alen + 18 + hmac_size] )
          {
LABEL_29:
            ndpi_set_detected_protocol(ndpi_struct, flow, 0x9Fu, 0);
            return;
          }
        }
      }
    }
    ++flow->ovpn_counter;
  }
}