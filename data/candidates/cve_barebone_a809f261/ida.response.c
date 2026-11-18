int __cdecl skip_boxes(JXLParseContext *ctx, const uint8_t *buf, int buf_size)
{
  int head_size; // [rsp+Ch] [rbp-44h]
  unsigned __int64 size; // [rsp+10h] [rbp-40h]
  GetByteContext gb; // [rsp+18h] [rbp-38h] BYREF
  int buf_sizea; // [rsp+34h] [rbp-1Ch]
  const uint8_t *bufa; // [rsp+38h] [rbp-18h]
  JXLParseContext *ctxa; // [rsp+40h] [rbp-10h]

  ctxa = ctx;
  bufa = buf;
  buf_sizea = buf_size;
  if ( ctx->skip > buf_size )
    return -1397118274;
  bufa += ctxa->skip;
  buf_sizea -= ctxa->skip;
  bytestream2_init(&gb, bufa, buf_sizea);
  while ( 1 )
  {
    head_size = 4;
    if ( bytestream2_peek_le16(&gb) == 2815 || bytestream2_peek_le64(&gb) == 0x204C584A0C000000LL )
      break;
    if ( bytestream2_get_bytes_left(&gb) < 8 )
      return -1397118274;
    size = bytestream2_get_be32(&gb);
    if ( size == 1 )
    {
      if ( bytestream2_get_bytes_left(&gb) < 12 )
        return -1397118274;
      size = bytestream2_get_be64(&gb);
      head_size = 12;
    }
    if ( !size )
      return -1094995529;
    if ( size <= head_size + 4 )
      return -1094995529;
    ctxa->skip += size;
    bytestream2_skip(&gb, size - head_size);
    if ( bytestream2_get_bytes_left(&gb) <= 0 )
      return -1397118274;
  }
  return 0;
}