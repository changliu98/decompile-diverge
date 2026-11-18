void __cdecl sha256_update(SHA256_CTX *ctx, const BYTE *data, size_t len)
{
  size_t i;

  for (i = 0; i < len; ++i)
  {
    // Append the current byte to the context's data buffer
    ctx->data[ctx->datalen++] = data[i];

    // When the buffer reaches 64 bytes, it's a full block ready to be processed
    if (ctx->datalen == 64)
    {
      sha256_transform(ctx, ctx->data);
      ctx->bitlen += 512;      // 64 bytes * 8 bits = 512 bits
      ctx->datalen = 0;        // Reset buffer length for the next block
    }
  }
}