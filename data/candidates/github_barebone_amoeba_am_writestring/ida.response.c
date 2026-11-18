int __cdecl am_writestring(am_DumpCtx *ctx, const char *name)
{
  int v2; // eax
  size_t v4; // [rsp+8h] [rbp-38h]
  size_t buflen; // [rsp+10h] [rbp-30h]
  am_Dumper *d; // [rsp+20h] [rbp-20h]

  d = ctx->dumper;
  if ( name )
    v4 = strlen(name);
  else
    v4 = 0LL;
  if ( v4 >= 0x100 )
    return -1;
  if ( v4 >= 0x20 )
  {
    if ( am_writechar(ctx, 217) )
      return -1;
    if ( am_writechar(ctx, v4) )
      return -1;
  }
  else if ( am_writechar(ctx, v4 + 160) )
  {
    return -1;
  }
  buflen = ctx->p - ctx->buf;
  if ( v4 + buflen > 0x1000 )
  {
    ctx->p = ctx->buf;
    if ( buflen )
    {
      v2 = d->writer(d, ctx->buf, buflen);
      ctx->ret = v2;
      if ( v2 )
        return -1;
    }
  }
  memcpy(ctx->p, name, v4);
  ctx->p += v4;
  return 0;
}