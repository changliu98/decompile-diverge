void md5_update(struct md5_ctx *ctx, unsigned char *buf, size_t len)
{
 size_t i = 0;

 while (i < len) {
  ctx->block[ctx->bpos] = buf[i];
  ctx->bpos++;
  if (ctx->bpos == 64) {
   md5_transform(ctx, ctx->block);
   ctx->len += 512;
   ctx->bpos = 0;
  }
  i++;
 }
}