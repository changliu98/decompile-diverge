int skip_boxes(JXLParseContext *ctx,uint8_t *buf,int buf_size)

{
  uint uVar1;
  int iVar2;
  uint64_t uVar3;
  int head_size;
  uint64_t size;
  GetByteContext gb;
  int buf_size_local;
  uint8_t *buf_local;
  JXLParseContext *ctx_local;
  
  if (ctx->skip <= buf_size) {
    bytestream2_init(&gb,buf + ctx->skip,buf_size - ctx->skip);
    do {
      head_size = 4;
      uVar1 = bytestream2_peek_le16(&gb);
      if ((uVar1 == 0xaff) || (uVar3 = bytestream2_peek_le64(&gb), uVar3 == 0x204c584a0c000000)) {
        return 0;
      }
      iVar2 = bytestream2_get_bytes_left(&gb);
      if (iVar2 < 8) {
        return -0x53465542;
      }
      uVar1 = bytestream2_get_be32(&gb);
      size = (uint64_t)uVar1;
      if (size == 1) {
        iVar2 = bytestream2_get_bytes_left(&gb);
        if (iVar2 < 0xc) {
          return -0x53465542;
        }
        size = bytestream2_get_be64(&gb);
        head_size = 0xc;
      }
      if (size == 0) {
        return -0x41444e49;
      }
      if (size <= (ulong)(long)(head_size + 4)) {
        return -0x41444e49;
      }
      ctx->skip = ctx->skip + (int)size;
      bytestream2_skip(&gb,(int)size - head_size);
      iVar2 = bytestream2_get_bytes_left(&gb);
    } while (0 < iVar2);
  }
  return -0x53465542;
}