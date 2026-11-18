static int try_read_command_binary(conn *c) {
  static int debug = 1;
  bin_header *h;
  int i;
  unsigned char buf[40];
  unsigned char keylen;
  unsigned short extralen;
  if (c->read_bytes < sizeof(bin_header)) {
    return 0;
  }
  c->bh = *(bin_header *)c->rcur;
  h = &c->bh;
  if (debug >= 2) {
    fprintf(stderr, "<%d Read binary protocol data:", c->sd);
    for (i = 0; i < sizeof(bin_header); i++) {
      if (i % 4 == 0) {
        fprintf(stderr, "\n<%d   ", c->sd);
      }
      fprintf(stderr, " 0x%02x", ((unsigned char *)&h->h)[i]);
    }
    fprintf(stderr, "\n");
  }
  c->bh = *h;
  c->bh.h.extralen = ntohs(h->h.extralen);
  c->bh.h.bodylen = ntohl(h->h.bodylen);
  c->bh.h.cas = ntohll(h->h.cas);
  if (c->bh.h.magic != 0x80) {
    if (debug) {
      fprintf(stderr, "Invalid magic:  %x\n", c->bh.h.magic);
    }
    conn_set_state(c, CONN_STATE_ERROR);
    return -1;
  }
  keylen = c->bh.h.keylen;
  extralen = c->bh.h.extralen;
  if (c->read_bytes < sizeof(bin_header) + keylen + extralen) {
    return 0;
  }
  if (resp_start(c) == 0) {
    conn_set_state(c, CONN_STATE_ERROR);
    return -1;
  }
  c->magic = c->bh.h.magic;
  c->keylen = c->bh.h.extralen;
  c->opcode = c->bh.h.opcode;
  c->datatype = 0;
  c->state = CONN_STATE_READ_BINARY_COMMAND;
  memcpy(buf + sizeof(bin_header), c->rcur + sizeof(bin_header), keylen);
  c->read_bytes -= sizeof(bin_header) + keylen + extralen;
  c->rcur += sizeof(bin_header) + keylen + extralen;
  dispatch_bin_command(c, buf);
  return 1;
}