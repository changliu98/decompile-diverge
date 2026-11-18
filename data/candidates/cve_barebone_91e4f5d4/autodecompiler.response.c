__attribute__((used)) static int try_read_command_binary(conn *c) {
    protocol_binary_request_header* header;
    int cmd;
    unsigned int keylen;
    unsigned char *extbuf;
    int extlen;
    int ret;

    if (c->binary_header_size < sizeof(header->bytes)) {
        // Wait for more data to come in.
        return 0;
    }

    c->binary_header.magic = c->binary_header.bytes[0];
    c->binary_header.opcode = c->binary_header.bytes[1];
    c->binary_header.keylen = c->binary_header.bytes[2] << 8 | c->binary_header.bytes[3];

    header = &c->binary_header;
    if (settings_0.verbose > 1) {
        int ii;
        fprintf(stderr, "<%d Read binary protocol data:", c->sfd);
        for (ii = 0; ii < sizeof(header->bytes); ++ii) {
            if (ii % 4 == 0) {
                fprintf(stderr, "\n<%d   ", c->sfd);
            }
            fprintf(stderr, " 0x%02x", header->bytes[ii]);
        }
        fprintf(stderr, "\n");
    }

    c->binary_header.magic = header->magic;
    c->binary_header.opcode = header->opcode;
    c->binary_header.keylen = ntohs(header->keylen);
    c->binary_header.extlen = ntohl(header->extlen);
    c->binary_header.bodylen = ntohll(header->bodylen);

    switch (header->magic) {
    case PROTOCOL_BINARY_REQ:
        cmd = header->opcode;
        break;
    default:
        if (settings_0.verbose) {
            fprintf(stderr, "Invalid magic:  %x\n", header->magic);
        }
        conn_set_state(c, conn_closing);
        return -1;
    }

    extlen = header->extlen;
    keylen = header->keylen;

    if (c->binary_header_size < sizeof(header->bytes) + extlen + keylen) {
        // Wait for more data to come in.
        return 0;
    }

    if (!resp_start(c)) {
        conn_set_state(c, conn_closing);
        return -1;
    }

    c->cmd = header->opcode;
    c->keylen = keylen;
    c->vbucket = header->vbucket;
    c->cas = 0;
    c->time_start = current_time;

    extbuf = c->binary_header.bytes + sizeof(header->bytes);
    memcpy(&extbuf[0], c->binary_header.bytes + sizeof(header->bytes), extlen);
    c->binary_header_size -= sizeof(header->bytes) + extlen + keylen;
    c->binary_header.bytes += sizeof(header->bytes) + extlen + keylen;

    dispatch_bin_command(c, extbuf);

    ret = 1;
    return ret;
}