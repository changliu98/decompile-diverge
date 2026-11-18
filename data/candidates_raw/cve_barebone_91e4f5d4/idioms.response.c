int conn_read_binary(struct conn *c)
{
  struct protocol_binary_request_header *header;
  struct protocol_binary_ext *ext;
  int i;
  struct protocol_binary_ext extbuf;
  struct conn *ca = c;
  if (ca->rbytes < sizeof(*header))
    return 0;
  ca->binary_header = *(struct protocol_binary_request_header *)ca->rcurr;
  header = &ca->binary_header;
  if (settings.debug > 1) {
    conn_log(stderr, "<%d Read binary protocol data:", ca->sfd);
    for (i = 0; i < sizeof(*header); i++) {
      if (i % 4 == 0)
        conn_log(stderr, "\n<%d   ", ca->sfd);
      conn_log(stderr, " 0x%02x", ((unsigned char *)header)[i]);
    }
    conn_log(stderr, "\n");
  }
  ca->binary_header = *header;
  ca->binary_header.request.keylen = __bswap_16 (ca->binary_header.request.keylen);
  ca->binary_header.request.bodylen = __bswap_32 (ca->binary_header.request.bodylen);
  ca->binary_header.request.cas = __bswap_64 (ca->binary_header.request.cas);
  if (ca->binary_header.request.magic != 0x80) {
    if (settings.debug)
      conn_log(stderr, "Invalid magic:  %x\n", ca->binary_header.request.magic);
    conn_setstate(ca, conn_closing);
    return -1;
  }
  ext = (struct protocol_binary_ext *)ca->rcurr + sizeof(*header);
  extlen = ext->extlen;
  keylen = ca->binary_header.request.keylen;
  if (ca->rbytes < sizeof(*header) + extlen + keylen)
    return 0;
  if (!conn_is_valid(ca))
    return -1;
  ca->cmd = ca->binary_header.request.opcode;
  ca->keylen = ca->binary_header.request.keylen;
  ca->opaque = ca->binary_header.request.opaque;
  ca->cas = 0;
  ca->last_cmd_time = current_time;
  memmove(&extbuf.extlen, ext, extlen);
  ca->rbytes -= sizeof(*header) + extlen + keylen;
  ca->rcurr += sizeof(*header) + extlen + keylen;
  conn_read_binary_key(ca, &extbuf);
  return 1;
}