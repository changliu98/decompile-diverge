u64 crypto_stream_chacha20_xor(u8 *cipher_text, const u8 *plain_text,
                               size_t text_size, const u8 key[32],
                               const u8 nonce[8], u64 ctr) {
    u32 input[16];
    u32 pool[16];

    load32_le_buf(input , chacha20_constant);
    load32_le_buf(input+4, key );
    load32_le_buf(input+14, nonce);
    input[12] = (u32)(ctr );
    input[13] = (u32)(ctr >> 32);

    size_t nb_blocks = text_size / 64;
    for (size_t i = 0; i < nb_blocks; i++) {
        chacha20_rounds(pool, input);
        if (plain_text != NULL) {
            for (size_t j = 0; j < 16; j++) {
                u32 x = pool[j] + input[j];
                store32_le(cipher_text, x ^ load32_le(plain_text));
                cipher_text += sizeof(u32);
                plain_text += sizeof(u32);
            }
        } else {
            for (size_t j = 0; j < 16; j++) {
                u32 x = pool[j] + input[j];
                store32_le(cipher_text, x);
                cipher_text += sizeof(u32);
            }
        }

        input[12]++;
        if (input[12] == 0) {
            input[13]++;
        }
    }

    u8 last_block[64];
    text_size &= 63;
    if (text_size > 0 || nb_blocks == 0) {
        if (plain_text == NULL) {
            plain_text = zero;
        }
        chacha20_rounds(pool, input);
        for (size_t j = 0; j < 16; j++) {
            store32_le(last_block + j * sizeof(u32), pool[j] + input[j]);
        }
        for (size_t j = 0; j < text_size; j++) {
            *cipher_text++ = last_block[j] ^ *plain_text++;
        }
        crypto_wipe(last_block, sizeof(last_block));
    }
    ctr = input[12] + ((u64)input[13] << 32) + (text_size > 0);
    crypto_wipe(pool , sizeof(pool ));
    crypto_wipe(input, sizeof(input));
    return ctr;
}