int dns_packet_is_reply_for(struct DNSPacket *packet, struct DNSResourceKey *key) {
    assert(packet != NULL);
    assert(key != NULL);

    // Check if the QR bit (bit 15 of the 16-bit word at offset 2) is set to 1 (Reply)
    uint16_t flags = be16toh(*(uint16_t *)((char *)DNS_PACKET_DATA(packet) + 2));
    if (((flags >> 15) & 1) != 1) {
        return 0;
    }

    int r = dns_packet_extract(packet);
    if (r < 0) {
        return r;
    }

    // Check if the type (at offset 4 of the resource struct) is 1
    struct DNSResourceKey *resource = (struct DNSResourceKey *)packet->data;
    if (*(int *)((char *)resource + 4) != 1) {
        return 0;
    }

    // Compare the resource key (at offset 16 of the resource struct) with the provided key
    struct DNSResourceKey *packet_key = (struct DNSResourceKey *)((char *)resource + 16);
    return dns_resource_key_equal(packet_key, key);
}