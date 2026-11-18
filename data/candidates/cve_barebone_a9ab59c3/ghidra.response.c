int dns_packet_is_reply_for(DnsPacket *p,DnsResourceKey *key)

{
  uint16_t uVar1;
  uint8_t *puVar2;
  int r;
  DnsResourceKey *key_local;
  DnsPacket *p_local;
  int local_c;
  
  if (p == (DnsPacket *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("p","/work/harness.c",0x2f3,
                  "int dns_packet_is_reply_for(DnsPacket *, const DnsResourceKey *)");
  }
  if (key == (DnsResourceKey *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("key","/work/harness.c",0x2f4,
                  "int dns_packet_is_reply_for(DnsPacket *, const DnsResourceKey *)");
  }
  puVar2 = DNS_PACKET_DATA(p);
  uVar1 = be16toh(*(be16_t *)(puVar2 + 2));
  if ((int)(uint)uVar1 >> 0xf == 1) {
    local_c = dns_packet_extract(p);
    if (-1 < local_c) {
      if (p->question->n_keys == 1) {
        local_c = dns_resource_key_equal(*(DnsResourceKey **)(p->question + 1),key);
      }
      else {
        local_c = 0;
      }
    }
  }
  else {
    local_c = 0;
  }
  return local_c;
}