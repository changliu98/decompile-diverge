void md5_update(MD5_CTX *ctx, unsigned char *input, unsigned long inputlen) {
  unsigned long i;
  for (i = 0; i < inputlen; ++i) {
    ctx->in[ctx->inlen] = input[i];
    ctx->inlen++;
    if (ctx->inlen == 64) {
      md5_transform(ctx, ctx->in);
      ctx->total += 512;
      ctx->inlen = 0;
    }
  }
}