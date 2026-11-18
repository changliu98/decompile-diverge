size_t crypto_chacha20_djb(
    unsigned char *cipher_text,
    const unsigned char *plain_text,
    size_t text_size,
    const unsigned char *key,
    const unsigned char *nonce,
    uint64_t ctr)
{
    uint32_t input[16];
    uint32_t pool[16];
    size_t nb_blocks;
    size_t leftover;
    size_t i, j;

    load32_le_buf(input, chacha20_constant, 4);
    load32_le_buf(input + 4, key, 8);
    load32_le_buf(input + 14, nonce, 2);
    input[12] = ctr;
    input[13] = ctr >> 32;

    nb_blocks = text_size / 64;
    for (i = 0; i < nb_blocks; i++) {
        chacha20_rounds(pool, input);
        if (plain_text) {
            for (j = 0; j < 16; j++) {
                store32_le(cipher_text, pool[j] + input[j] ^ load32_le(plain_text));
                cipher_text += 4;
                plain_text += 4;
            }
        } else {
            for (j = 0; j < 16; j++) {
                store32_le(cipher_text, pool[j] + input[j]);
                cipher_text += 4;
            }
        }
        if (++input[12] == 0) {
            input[13]++;
        }
    }

    leftover = text_size % 64;
    if (leftover) {
        unsigned char tmp[64];

        if (!plain_text) {
            plain_text = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
                         "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
        }
        chacha20_rounds(pool, input);
        for (i = 0; i < 16; i++) {
            store32_le(tmp + 4 * i, pool[i] + input[i]);
        }
        for (i = 0; i < leftover; i++) {
            cipher_text[i] = plain_text[i] ^ tmp[i];
        }
        crypto_wipe(tmp, 64);
    }

    crypto_wipe(pool, 64);
    crypto_wipe(input, 64);

    return nb_blocks + (leftover != 0);
}