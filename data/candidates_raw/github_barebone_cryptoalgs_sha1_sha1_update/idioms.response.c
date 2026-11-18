void sha1_update(struct sha1_context *ctx, unsigned char *data, unsigned long len)
{
  unsigned long i;
  for (i = 0; i < len; i++)
  {
    ctx->data[ctx->datalen] = data[i];
    ctx->datalen++;
    if (ctx->datalen == 64)
    {
      sha1_transform (ctx, ctx->data);
      ctx->bitlen += 512;
      ctx->datalen = 0;
    }
  }
}