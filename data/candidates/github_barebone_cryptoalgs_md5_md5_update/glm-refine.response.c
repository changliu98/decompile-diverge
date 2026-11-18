void __cdecl md5_update(MD5_CTX *ctx, const BYTE *data, size_t len)
{
  for (size_t i = 0; i < len; ++i)
  {
    // Fill the context's internal buffer byte by byte
    ctx->data[ctx->datalen++] = data[i];

    // When the 64-byte block is full, process it
    if (ctx->datalen == 64)
    {
      md5_transform(ctx, ctx->data);
      ctx->bitlen += 512;  // 64 bytes * 8 bits = 512 bits
      ctx->datalen = 0;    // Reset buffer for the next block
    }
  }
}