int __cdecl dns_packet_is_reply_for(DnsPacket *p, const DnsResourceKey *key)
{
  uint8_t *packet_data;
  int ret;

  // Validate arguments
  if (!p)
    __assert_fail("p", "/work/harness.c", 0x2F3u, "int dns_packet_is_reply_for(DnsPacket *, const DnsResourceKey *)");
  if (!key)
    __assert_fail("key", "/work/harness.c", 0x2F4u, "int dns_packet_is_reply_for(DnsPacket *, const DnsResourceKey *)");

  packet_data = DNS_PACKET_DATA(p);

  // Check the QR (Query/Response) flag in the DNS header.
  // The flags are located at offset 2 (i.e., 16-bit word 1) in the DNS packet.
  // The QR flag is the most significant bit (bit 15).
  uint16_t flags = *((uint16_t *)packet_data + 1);
  if (((foldCase(flags) >> 15) & 1) != 1)
    return 0;

  // Extract the DNS packet structure
  ret = dns_packet_extract(p);
  if (ret < 0)
    return ret;

  // Ensure there is exactly one question in the packet
  if (p->question->n_keys == 1)
    return dns_resource_key_equal(p->question->keys[0], key);

  return 0;
}