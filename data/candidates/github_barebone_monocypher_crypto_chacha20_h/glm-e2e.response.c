void crypto_chacha20_h(uint8_t *out, const uint8_t *key, const uint8_t *nonce) {
    uint32_t state[16];

    // Load constants into state[0..3]
    load32_le_buf(state, (const uint8_t *)chacha20_constant, 4);

    // Load 256-bit key into state[4..11]
    load32_le_buf(state + 4, key, 8);

    // Load 96-bit nonce into state[12..15]
    // (Note: state[12] is typically the counter, but here it's loaded directly from the nonce)
    load32_le_buf(state + 12, nonce, 4);

    // Perform ChaCha20 rounds
    chacha20_rounds(state, state);

    // Store the first 16 bytes of the state to the output buffer
    store32_le_buf(out, state, 4);

    // Store the last 16 bytes of the state to out + 16
    store32_le_buf(out + 16, state + 12, 4);

    // Securely wipe the state from the stack
    crypto_wipe(state, 64);
}