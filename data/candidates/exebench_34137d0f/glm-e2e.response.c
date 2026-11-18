void sha_init(struct sha_ctx *ctx) {
    ctx->h0 = 0x67452301;
    ctx->h1 = 0xefcdab89;
    ctx->h2 = 0x98badcfe;
    ctx->h3 = 0x10325476;
    ctx->h4 = 0xc3d2e1f0;
}