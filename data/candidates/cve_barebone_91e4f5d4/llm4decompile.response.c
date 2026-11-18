rstatus_t try_read_command_binary(conn *c) {
    protocol_binary_request_header *request;
    uint8_t extlen = 0;
    char extbuf[40];
    int ii;

    if (c->rbytes < sizeof(protocol_binary_request_header)) {
        return 0;
    }

    request = (protocol_binary_request_header *)c->rcurr;
    c->binary_header = *request;

    if (settings.verbose > 1) {
        fprintf(stderr, "<%d Read binary protocol data:", c->sfd);
        for (ii = 0; ii < sizeof(protocol_binary_request_header); ii++) {
            if (ii % 4 == 0) {
                fprintf(stderr, "\n<%d   ", c->sfd);
            }
            fprintf(stderr, " 0x%02x", ((uint8_t*)&c->binary_header)[ii]);
        }
        fprintf(stderr, "\n");
    }

    c->binary_header.request.keylen = ntohs(c->binary_header.request.keylen);
    c->binary_header.request.bodylen = ntohl(c->binary_header.request.bodylen);
    c->binary_header.request.cas = ntohll(c->binary_header.request.cas);

    if (c->binary_header.request.magic != 0x80) {
        if (settings.verbose) {
            fprintf(stderr, "Invalid magic:  %x\n", c->binary_header.request.magic);
        }
        conn_set_state(c, conn_closing);
        return -1;
    }

    extlen = c->binary_header.request.extlen;
    if (c->rbytes < (sizeof(protocol_binary_request_header) + extlen +
                     c->binary_header.request.keylen)) {
        return 0;
    }

    if (!resp_start(c)) {
        conn_set_state(c, conn_closing);
        return -1;
    }

    c->cmd = c->binary_header.request.opcode;
    c->keylen = c->binary_header.request.keylen;
    c->opaque = c->binary_header.request.opaque;
    c->cas = 0;
    c->last_cmd_time = current_time;

    memcpy(extbuf + sizeof(protocol_binary_request_header),
           c->rcurr + sizeof(protocol_binary_request_header), extlen);

    c->rbytes -= (sizeof(protocol_binary_request_header) + extlen +
                  c->binary_header.request.keylen);
    c->rcurr += (sizeof(protocol_binary_request_header) + extlen +
                 c->binary_header.request.keylen);

    dispatch_bin_command(c, extbuf);
    return 1;
}