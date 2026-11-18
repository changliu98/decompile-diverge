int __cdecl dns_packet_is_reply_for(DnsPacket *p, const DnsResourceKey *key)
{
  uint8_t *v2; // rax
  int r; // [rsp+4h] [rbp-1Ch]

  if ( !p )
    __assert_fail("p", "/work/harness.c", 0x2F3u, "int dns_packet_is_reply_for(DnsPacket *, const DnsResourceKey *)");
  if ( !key )
    __assert_fail("key", "/work/harness.c", 0x2F4u, "int dns_packet_is_reply_for(DnsPacket *, const DnsResourceKey *)");
  v2 = DNS_PACKET_DATA(p);
  if ( (((int)foldCase(*((_WORD *)v2 + 1)) >> 15) & 1) != 1 )
    return 0;
  r = dns_packet_extract(p);
  if ( r < 0 )
    return r;
  if ( p->question->n_keys == 1 )
    return dns_resource_key_equal(p->question->keys[0], key);
  return 0;
}