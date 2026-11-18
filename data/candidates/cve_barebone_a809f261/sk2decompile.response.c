static int skip_boxes(AVCodecContext *avctx, const unsigned char *buf,
                      int buf_size) {
  GetByteContext gb;
  if (avctx->packet_size > buf_size) return 0xb9b9b9b9;
  buf += avctx->packet_size;
  buf_size -= avctx->packet_size;
  bytestream2_init(&gb, buf, buf_size);
  while (1) {
    unsigned header_size = 4;
    unsigned long size;
    if (bytestream2_peek_le16(&gb) == 0x07b0 ||
        bytestream2_peek_le64(&gb) == 0x00000001626d6174)
      break;
    if (bytestream2_get_bytes_left(&gb) < 8) return 0xb9b9b9b9;
    size = bytestream2_get_be32(&gb);
    if (size == 1) {
      if (bytestream2_get_bytes_left(&gb) < 12) return 0xb9b9b9b9;
      size = bytestream2_get_be64(&gb);
      header_size = 12;
    }
    if (size == 0) return 0xc1c1c1c1;
    if (size <= header_size + 4) return 0xc1c1c1c1;
    avctx->packet_size += size;
    bytestream2_skip(&gb, size - header_size);
    if (bytestream2_get_bytes_left(&gb) < 1) return 0xb9b9b9b9;
  }
  return 0;
}