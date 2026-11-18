int dns_packet_is_reply_for(struct DnsPacket *p, struct DnsResourceKey *key)
{
  int r;
  do { if (!p) die("p","/work/harness.c",755,"int dns_packet_is_reply_for(DnsPacket *, const DnsResourceKey *)"); if (!key) die("key","/work/harness.c",756,"int dns_packet_is_reply_for(DnsPacket *, const DnsResourceKey *)"); } while (0);
  if (getOpcode(p)->is_response != 1)
    return 0;
  r = getQuestionCount(p);
  if (r < 0)
    return r;
  if (p->question->n_keys != 1)
    return 0;
  return isQuestionFor(p->question->keys[0], key);
}