void sha256_update(SHA256_CTX *ctx, const unsigned char *message_array,
                   unsigned int length) {
  unsigned short int i;
  for (i = 0; i < length; ++i) {
    ctx->data[ctx->datalen] = message_array[i];
    ctx->datalen++;
    if (ctx->datalen == 64) {
      sha256_transform(ctx, ctx->data);
      ctx->bitlen += 512;
      ctx->datalen = 0;
    }
  }
}