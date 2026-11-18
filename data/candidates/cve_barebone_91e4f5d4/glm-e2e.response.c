int try_read_command_binary(conn *c) {
    if (c->msgsize < 24) {
        return 0;
    }

    // Copy 24 bytes from c->rcurr to c->binary_header
    memcpy(&c->binary_header, c->rcurr, 24);

    protocol_binary_request_header_1 *hdr = &c->binary_header;

    if (settings > 1) {
        fprintf(stderr, "%d: Reading binary protocol data:\n", c->sfd);
        for (int i = 0; i < 24; i++) {
            if (i % 4 == 0) {
                fprintf(stderr, "%d:   %d: ", c->sfd, i);
            }
            fprintf(stderr, " 0x%02x", ((unsigned char *)hdr)[i]);
        }
        fprintf(stderr, "\n");
    }

    // Re-copy the header (likely to ensure proper alignment or just redundant code)
    memcpy(&c->binary_header, c->rcurr, 24);

    c->binary_header.request.keylen = ntohs(hdr->request.keylen);
    c->binary_header.request.bodylen = ntohl(hdr->request.bodylen);
    c->binary_header.request.cas = ntohll(hdr->request.cas);

    if (c->binary_header.request.opcode != 0x80) {
        if (settings != 0) {
            fprintf(stderr, "%d: Invalid binary protocol request opcode: 0x%02x\n", c->sfd, c->binary_header.request.opcode);
        }
        conn_set_state(c, 8);
        return -1;
    }

    uint8_t extlen = c->binary_header.request.extlen;
    uint16_t keylen = c->binary_header.request.keylen;

    if (c->msgsize < (int)(extlen + keylen + 24)) {
        return 0;
    }

    if (!resp_start(c)) {
        conn_set_state(c, 8);
        return -1;
    }

    c->item_cmd = c->binary_header.request.opcode_1;
    c->item_keylen = c->binary_header.request.keylen;
    c->item_extlen = c->binary_header.request.extlen;
    c->item_cas = 0;
    c->last_cmd_time = current_time;

    // Copy the extension data to a local buffer
    char ext[32];
    memcpy(ext + 24, c->rcurr + 24, extlen);

    c->msgsize -= (extlen + keylen + 24);
    c->rcurr += (extlen + keylen + 24);

    dispatch_bin_command(c, ext);

    return 1;
}