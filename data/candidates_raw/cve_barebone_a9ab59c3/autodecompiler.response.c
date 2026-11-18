int dns_packet_is_reply_for(DnsPacket *p, const DnsResourceKey *key) {
        int r;

        assert__bench(p);
        assert__bench(key);

        if (!(((((unsigned short) (__ZL8foldCaset((DNS_PACKET_DATA(p)[1])))) >> 15) & 1) == 1))
                return 0;

        r = dns_packet_extract(p);
        if (r < 0)
                return r;
        if (p->question->n_keys != 1)
                return 0;

        return dns_resource_key_equal(p->question->keys[0], key);
}