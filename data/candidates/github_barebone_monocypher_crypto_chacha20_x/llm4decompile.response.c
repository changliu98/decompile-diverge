size_t crypto_chacha20_x(
    unsigned char *cipher_text,
    const unsigned char *plain_text,
    size_t text_size,
    const unsigned char *key,
    const unsigned char *nonce,
    uint64_t ctr
)
{
    unsigned char sub_key[32];
    size_t result;

    crypto_chacha20_h(sub_key, key, nonce);
    result = crypto_chacha20_djb(cipher_text, plain_text, text_size, sub_key, nonce + 16, ctr);
    crypto_wipe(sub_key, 32);

    return result;
}