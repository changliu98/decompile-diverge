u64 crypto_xchacha20(u8 *cipher_text, const u8 *plain_text,
                     size_t text_size, const u8 key[32],
                     const u8 nonce[24], u64 ctr) {
    u8 sub_key[32];
    crypto_chacha20_h(sub_key, key, nonce);
    ctr = crypto_chacha20_djb(cipher_text, plain_text, text_size,
                              sub_key, nonce + 16, ctr);
    crypto_wipe(sub_key, sizeof(sub_key));
    return ctr;
}