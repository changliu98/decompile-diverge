void __cdecl md5_update(MD5_CTX *ctx, const BYTE *data, size_t len)
{
  size_t i; // [rsp+0h] [rbp-20h]

  for ( i = 0LL; i < len; ++i )
  {
    ctx->data[ctx->datalen++] = data[i];
    if ( ctx->datalen == 64 )
    {
      md5_transform(ctx, ctx->data);
      ctx->bitlen += 512LL;
      ctx->datalen = 0;
    }
  }
}