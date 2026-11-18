void ndpi_search_oracle(ndpi_detection_module_struct *ndpi_struct,ndpi_flow_struct *flow)

{
  uint16_t uVar1;
  uint16_t uVar2;
  u_int16_t sport;
  u_int16_t dport;
  ndpi_packet_struct *packet;
  ndpi_flow_struct *flow_local;
  ndpi_detection_module_struct *ndpi_struct_local;
  
  if ((flow->packet).tcp != (ndpi_tcphdr *)0x0) {
    uVar1 = ntohs(((flow->packet).tcp)->source);
    uVar2 = ntohs(((flow->packet).tcp)->dest);
    if (((uVar2 == 0x5f1) || (uVar1 == 0x5f1)) &&
       (((*(flow->packet).payload == '\a' &&
         (((flow->packet).payload[1] == 0xff && ((flow->packet).payload[2] == '\0')))) ||
        ((0xe7 < (flow->packet).payload_packet_len &&
         ((((*(flow->packet).payload == '\0' || (*(flow->packet).payload == '\x01')) &&
           ((flow->packet).payload[1] != '\0')) &&
          (((flow->packet).payload[2] == '\0' && ((flow->packet).payload[3] == '\0')))))))))) {
      ndpi_int_oracle_add_connection(ndpi_struct,flow);
    }
    else if (((((flow->packet).payload_packet_len == 0xd5) &&
              ((*(flow->packet).payload == '\0' && ((flow->packet).payload[1] == 0xd5)))) &&
             ((flow->packet).payload[2] == '\0')) && ((flow->packet).payload[3] == '\0')) {
      ndpi_int_oracle_add_connection(ndpi_struct,flow);
    }
  }
  return;
}