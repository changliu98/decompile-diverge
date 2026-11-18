void __cdecl ndpi_search_oracle(ndpi_detection_module_struct *ndpi_struct, ndpi_flow_struct *flow)
{
  u_int16_t sport; // [rsp+4h] [rbp-1Ch]

  if ( flow->packet.tcp )
  {
    if ( ((sport = ntohs(flow->packet.tcp->source), ntohs(flow->packet.tcp->dest) == 1521) || sport == 1521)
      && (*flow->packet.payload == 7
       && *((unsigned __int8 *)flow->packet.payload + 1) == 255
       && !*((_BYTE *)flow->packet.payload + 2)
       || flow->packet.payload_packet_len >= 0xE8u
       && (!*flow->packet.payload || *flow->packet.payload == 1)
       && *((_BYTE *)flow->packet.payload + 1)
       && !*((_BYTE *)flow->packet.payload + 2)
       && !*((_BYTE *)flow->packet.payload + 3))
      || flow->packet.payload_packet_len == 213
      && !*flow->packet.payload
      && *((unsigned __int8 *)flow->packet.payload + 1) == 213
      && !*((_BYTE *)flow->packet.payload + 2)
      && !*((_BYTE *)flow->packet.payload + 3) )
    {
      ndpi_int_oracle_add_connection(ndpi_struct, flow);
    }
  }
}