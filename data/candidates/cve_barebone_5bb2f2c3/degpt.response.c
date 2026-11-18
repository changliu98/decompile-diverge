void ndpi_search_openvpn(ndpi_detection_module_struct *ndpi_struct,ndpi_flow_struct *flow)

{
  byte bVar1;
  int8_t iVar2;
  int8_t failed;
  int8_t hmac_size;
  u_int8_t alen;
  u_int8_t opcode;
  u_int8_t *session_remote;
  u_int8_t *ovpn_payload;
  ndpi_packet_struct *packet;
  ndpi_flow_struct *flow_local;
  ndpi_detection_module_struct *ndpi_struct_local;
  
  ovpn_payload = (flow->packet).payload;
  if (0x27 < (flow->packet).payload_packet_len) {
    if ((flow->packet).tcp != (ndpi_tcphdr *)0x0) {
      ovpn_payload = ovpn_payload + 2;
    }
    bVar1 = *ovpn_payload & 0xf8;
    if ((((flow->packet).udp == (ndpi_udphdr *)0x0) || (flow->num_processed_pkts != '\x01')) ||
       ((((flow->packet).payload_packet_len != 0x70 || ((bVar1 != 0xa8 && (bVar1 != 0xc0)))) &&
        (((flow->packet).payload_packet_len != 0x50 ||
         ((((bVar1 != 0xb8 && (bVar1 != 0x58)) && (bVar1 != 0xa0)) &&
          ((bVar1 != 0xa8 && (bVar1 != 200)))))))))) {
      if ((flow->ovpn_counter < 5) && ((bVar1 == 8 || (bVar1 == 0x38)))) {
        iVar2 = check_pkid_and_detect_hmac_size(ovpn_payload);
        if ('\0' < iVar2) {
          *(undefined8 *)flow->ovpn_session_id = *(undefined8 *)(ovpn_payload + 1);
        }
      }
      else if ((flow->ovpn_counter != '\0') &&
              ((flow->ovpn_counter < 6 &&
               ((((bVar1 == 0x10 || (bVar1 == 0x40)) &&
                 (iVar2 = check_pkid_and_detect_hmac_size(ovpn_payload), '\0' < iVar2)) &&
                ((ovpn_payload[iVar2 + 0x11] != 0 &&
                 (*(long *)flow->ovpn_session_id ==
                  *(long *)(ovpn_payload +
                           (long)(int)((uint)ovpn_payload[iVar2 + 0x11] << 2) +
                           (long)(iVar2 + 0x11) + 1))))))))) {
        ndpi_set_detected_protocol(ndpi_struct,flow,0x9f,0);
        return;
      }
      flow->ovpn_counter = flow->ovpn_counter + '\x01';
    }
    else {
      ndpi_set_detected_protocol(ndpi_struct,flow,0x9f,0);
    }
  }
  return;
}