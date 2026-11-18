define JXL_SIG_BOX_JXLC     2815

int __cdecl skip_boxes(JXLParseContext *ctx, const uint8_t *buf, int buf_size)
{
  GetByteContext gb;
  unsigned __int64 size;
  int head_size;

  if (ctx->skip > buf_size)
    return AVERROR_EOF;

  // Adjust buffer to skip already processed data
  buf += ctx->skip;
  buf_size -= ctx->skip;

  bytestream2_init(&gb, buf, buf_size);

  while (1)
  {
    // Check for JXLC (0x6A786C63 -> little-endian 2815) or JXLP boxes
    if (bytestream2_peek_le16(&gb) == JXL_SIG_BOX_JXLC || 
        bytestream2_peek_le64(&gb) == JXL_SIG_BOX_JXLP)
      break;

    if (bytestream2_get_bytes_left(&gb) < 8)
      return AVERROR_EOF;

    head_size = 4;
    size = bytestream2_get_be32(&gb);

    // If size is 1, the actual size is a 64-bit integer (extended box)
    if (size == 1)
    {
      if (bytestream2_get_bytes_left(&gb) < 12)
        return AVERROR_EOF;
      size = bytestream2_get_be64(&gb);
      head_size = 12;
    }

    // Size must be strictly greater than header size + 4 (box type)
    if (!size || size <= head_size + 4)
      return AVERROR_INVALIDDATA;

    ctx->skip += size;
    bytestream2_skip(&gb, size - head_size);

    if (bytestream2_get_bytes_left(&gb) <= 0)
      return AVERROR_EOF;
  }

  return 0;
}