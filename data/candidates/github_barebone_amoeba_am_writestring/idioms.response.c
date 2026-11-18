int am_writestring(struct am_DumpCtx *ctx, char *name)
{
  struct am_Dumper *d = ctx->dumper;
  unsigned long len;
  unsigned long n;
  if (name == ((void *)0))
    len = 0;
  else
    len = strlen(name);
  if (len >= 256)
    return -1;
  if (len < 32) {
    if (am_writechar(ctx, len + 0xa0))
      return -1;
  }
  else {
    if (am_writechar(ctx, 0xd1))
      return -1;
    if (am_writechar(ctx, len))
      return -1;
  }
  n = ctx->p - ctx->buf;
  if (n + len > 4096) {
    ctx->p = ctx->buf;
    if (n > 0) {
      ctx->ret = d->writer(d, ctx->buf, n);
      if (ctx->ret != 0)
        return -1;
    }
  }
  memcpy(ctx->p, name, len);
  ctx->p += len;
  return 0;
}