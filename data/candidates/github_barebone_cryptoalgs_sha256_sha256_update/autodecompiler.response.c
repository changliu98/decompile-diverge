void sha256(sha256_ctx_t *ctx, unsigned char *buf, size_t len)
{
 memset__bench(ctx, 0, sizeof(sha256_ctx_t));

 sha256_init(ctx);

 sha256_update(ctx, buf, len);

 sha256_final(ctx, buf);
}