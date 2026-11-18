void __cdecl sha256_update(SHA256_CTX *ctx, const BYTE *data, size_t len)
{
  WORD i; // [rsp+4h] [rbp-1Ch]

  for ( i = 0; i < len; ++i )
  {
    ctx->data[ctx->datalen++] = data[i];
    if ( ctx->datalen == 64 )
    {
      sha256_transform(ctx, ctx->data);
      ctx->bitlen += 512LL;
      ctx->datalen = 0;
    }
  }
}