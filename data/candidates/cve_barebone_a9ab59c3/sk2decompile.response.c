int dns_packet_is_reply_for(DnsPacket *p, const DnsResourceKey *q) {
  int r;
  assert(p);
  assert(q);
  if ((((foldCase(p->header->flags) >> 15) & 1) != 1)) return 0;
  r = dns_packet_extract(p);
  if (r < 0) return r;
  if (p->question->count != 1) return 0;
  return dns_resource_key_equal(p->question->keys[0], q);
}