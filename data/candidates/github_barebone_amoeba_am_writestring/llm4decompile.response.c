int am_writestring(am_DumpCtx *ctx, const char *name)
{
  am_Dumper *d = ctx->dumper;
  size_t namelen = name ? strlen(name) : 0;

  if (namelen > 255 || namelen > 255)
    return -1;

  if (namelen < 32) {
    if (am_writechar(ctx, 0xa0 + namelen))
      return -1;
  } else {
    if (am_writechar(ctx, 0xd9))
      return -1;
    if (am_writechar(ctx, namelen))
      return -1;
  }


  if (namelen + (ctx->p - ctx->buf) > 4096) {
    size_t buf_len = ctx->p - ctx->buf;
    ctx->p = ctx->buf;
    if (buf_len) {
      ctx->ret = d->writer(d, ctx->buf, buf_len);
      if (ctx->ret)
        return -1;
    }
    if (namelen > 4096) {
      ctx->ret = d->writer(d, name, namelen);
      return ctx->ret;
    }
  }

  memcpy(ctx->p, name, namelen);
  ctx->p += namelen;
  return 0;
}