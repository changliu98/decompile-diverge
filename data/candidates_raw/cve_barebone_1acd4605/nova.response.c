static int func0(struct st_ptls_traffic_protection_t *ctx, const void *src, ptls_cipher_context_t *cipher_ctx)
{
    uint16_t seq = (uint16_t)ptls_get_uint(src + 2, 2);
    uint8_t *dst = ctx->secret;

    for (;;) {
        assert(ctx->nb_rounds!= 0);
        static const uint8_t prefix[4] = {0x00, 0x00, 0x00, 0x01};
        static const uint8_t postfix[4] = {0x00, 0x00, 0x00, 0x00};
        uint8_t *iv = ctx->iv;
        ptls_cipher_context_t *cipher_ctx2 = &ctx->traffic_protection_cipher_ctx;
        ptls_cipher_init(cipher_ctx2, &ptls_aes_gcm_128, dst, seq);
        ptls_cipher_update(cipher_ctx2, prefix, 4);
        ptls_cipher_update(cipher_ctx2, src + 4, cipher_ctx->aad_size - 4);
        ptls_cipher_final(cipher_ctx2, dst + 16);
        ptls_cipher_init(cipher_ctx, &ptls_aes_gcm_128, dst, seq);
        ptls_cipher_update(cipher_ctx, src + 4, cipher_ctx->aad_size - 4);
        ptls_cipher_final(cipher_ctx, iv + 16);
        switch (src + 1) {
        case 0x00:
            ptls_cipher_init(cipher_ctx, &ptls_aes_gcm_128, dst, seq);
            ptls_cipher_update(cipher