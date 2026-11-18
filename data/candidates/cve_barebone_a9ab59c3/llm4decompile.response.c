int dns_packet_is_reply_for(DnsPacket *p, const DnsResourceKey *key) {
        int r;

        do { if (!(p)) __assert_fail("p", "/work/harness.c", 755, "int dns_packet_is_reply_for(DnsPacket *, const DnsResourceKey *)"); } while (false);
        do { if (!(key)) __assert_fail("key", "/work/harness.c", 756, "int dns_packet_is_reply_for(DnsPacket *, const DnsResourceKey *)"); } while (false);

        if ((be16toh(((DnsPacketHeader *) DNS_PACKET_DATA(p))->flags) >> 15) != 1)
                return 0;

        r = dns_packet_extract(p);
        if (r < 0)
                return r;

        if (p->question->n_keys != 1)
                return 0;

        return dns_resource_key_equal(p->question->keys[0], key);
}