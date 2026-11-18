void sha1_update(SHA1_CTX *ctx,BYTE *data,size_t len)

{
  size_t i;
  size_t len_local;
  BYTE *data_local;
  SHA1_CTX *ctx_local;
  
  for (i = 0; i < len; i = i + 1) {
    ctx->data[ctx->datalen] = data[i];
    ctx->datalen = ctx->datalen + 1;
    if (ctx->datalen == 0x40) {
      sha1_transform(ctx,ctx->data);
      ctx->bitlen = ctx->bitlen + 0x200;
      ctx->datalen = 0;
    }
  }
  return;
}