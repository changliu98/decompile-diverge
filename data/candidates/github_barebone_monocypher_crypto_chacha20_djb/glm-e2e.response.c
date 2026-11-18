uint64_t crypto_chacha20_djb(uint8_t *out, const uint8_t *in, uint64_t in_len,
                             const uint8_t *key, const uint8_t *nonce, uint64_t counter)
{
    uint32_t state[16];
    uint32_t block[16];
    uint8_t block_bytes[64];
    
    uint32_t counter_lo = (uint32_t)counter;
    uint32_t counter_hi = (uint32_t)(counter >> 32);
    uint64_t n_blocks = in_len >> 6;
    uint64_t i;

    // Initialize state
    load32_le_buf(state, (const uint8_t *)chacha20_constant, 4);
    load32_le_buf(state + 4, key, 8);
    load32_le_buf(state + 14, nonce, 2);

    // Process full 64-byte blocks
    for (i = 0; i < n_blocks; i++) {
        chacha20_rounds(block, state);

        if (in != NULL) {
            for (size_t j = 0; j < 16; j++) {
                uint32_t val = block[j] + state[j];
                uint32_t in_val = load32_le(in);
                store32_le(out, in_val ^ val);
                out += 4;
                in += 4;
            }
        } else {
            for (size_t j = 0; j < 16; j++) {
                store32_le(out, block[j] + state[j]);
                out += 4;
            }
        }

        // Increment 64-bit counter
        counter_lo++;
        if (counter_lo == 0) {
            counter_hi++;
        }
    }

    // Process remaining bytes
    in_len &= 0x3f;
    if (in_len > 0) {
        if (in == NULL) {
            in = zero;
        }

        chacha20_rounds(block, state);

        for (size_t j = 0; j < 16; j++) {
            store32_le(block_bytes + j * 4, block[j] + state[j]);
        }

        for (size_t j = 0; j < in_len; j++) {
            out[j] = in[j] ^ block_bytes[j];
        }

        crypto_wipe(block_bytes, 64);
    }

    // Reconstruct 64-bit counter and add 1 if there was a remainder
    uint64_t final_counter = (uint64_t)counter_lo | ((uint64_t)counter_hi << 32);
    if (in_len > 0) {
        final_counter++;
    }

    crypto_wipe(block, 64);
    crypto_wipe(state, 64);

    return final_counter;
}