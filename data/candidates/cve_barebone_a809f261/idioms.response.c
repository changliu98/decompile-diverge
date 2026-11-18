int skip_boxes(struct JXLParseContext *ctx, void *buf, int buf_size) {
  struct GetByteContext gb;
  int size;
  int head_size;
  if (ctx->skip > buf_size)
    return -1397118274;
  buf = (uint8_t *)buf + ctx->skip;
  buf_size -= ctx->skip;
  getbyte_init(&gb, buf, buf_size);
  for (;;) {
    head_size = 4;
    if (getbyte_get(&gb) == 0x11 || getbyte_get64(&gb) == 0x0000000c004c584ajll)
      break;
    if (getbyte_get32(&gb) < 8)
      return -1397118274;
    size = getbyte_get32be(&gb);
    if (size == 1) {
      if (getbyte_get32(&gb) < 12)
        return -1397118274;
      size = getbyte_get32be(&gb);
      head_size = 12;
    }
    if (size == 0)
      return -1094995529;
    if (size <= (int)(head_size + 4))
      return -1094995529;
    ctx->skip += size;
    getbyte_skip(&gb, size - head_size);
    if (getbyte_get32(&gb) < 1)
      return -1397118274;
  }
  return 0;
}