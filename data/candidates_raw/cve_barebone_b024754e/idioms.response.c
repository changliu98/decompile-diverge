void ndpi_check_for_oracle(struct ndpi_detection_module *ndpi, struct ndpi_flow *flow)
{
    unsigned int dest;
    if (flow->packet.tcp == ((void *)0))
        return;
    dest = get_port(flow->packet.tcp->dest);
    if ((get_port(flow->packet.tcp->source) == 1521 || dest == 1521) &&
        ((flow->packet.payload[0] == 0x07 && flow->packet.payload[1] == 0xff && flow->packet.payload[2] == 0 &&
         flow->packet.payload[3] == 0) ||
         (flow->packet.payload_packet_len >= 232 &&
          (flow->packet.payload[0] == 0 || flow->packet.payload[0] == 1) &&
          flow->packet.payload[1] != 0 && flow->packet.payload[2] == 0 && flow->packet.payload[3] == 0) ||
         (flow->packet.payload_packet_len == 213 &&
          flow->packet.payload[0] == 0 &&
          flow->packet.payload[1] == 213 &&
          flow->packet.payload[2] == 0 &&
          flow->packet.payload[3] == 0)))
    {
        ndpi_set_oracle(ndpi, flow);
    }
    return;
}