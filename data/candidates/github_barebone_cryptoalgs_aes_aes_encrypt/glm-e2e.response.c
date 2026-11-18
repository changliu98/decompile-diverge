void aes_encrypt(const uint8_t *input, uint8_t *output, const uint8_t *expanded_key, uint32_t key_size) {
    uint8_t state[16];

    // Load input into state (transposing from column-major to row-major)
    state[0]  = input[0];
    state[1]  = input[4];
    state[2]  = input[8];
    state[3]  = input[12];
    state[4]  = input[1];
    state[5]  = input[5];
    state[6]  = input[9];
    state[7]  = input[13];
    state[8]  = input[2];
    state[9]  = input[6];
    state[10] = input[10];
    state[11] = input[14];
    state[12] = input[3];
    state[13] = input[7];
    state[14] = input[11];
    state[15] = input[15];

    // Initial round
    AddRoundKey(state, expanded_key);

    // Rounds 1 to 9
    for (int i = 1; i <= 9; i++) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, expanded_key + i * 16);
    }

    // Conditional rounds based on key size
    if (key_size == 0x80) {
        // AES-128: Final round (Round 10)
        SubBytes(state);
        ShiftRows(state);
        AddRoundKey(state, expanded_key + 0xa0);
    } else {
        // Rounds 10 and 11 (AES-192 and AES-256)
        for (int i = 10; i <= 11; i++) {
            SubBytes(state);
            ShiftRows(state);
            MixColumns(state);
            AddRoundKey(state, expanded_key + i * 16);
        }

        if (key_size == 0xc0) {
            // AES-192: Final round (Round 12)
            SubBytes(state);
            ShiftRows(state);
            AddRoundKey(state, expanded_key + 0xc0);
        } else {
            // Rounds 12 and 13 (AES-256)
            for (int i = 12; i <= 13; i++) {
                SubBytes(state);
                ShiftRows(state);
                MixColumns(state);
                AddRoundKey(state, expanded_key + i * 16);
            }
            // AES-256: Final round (Round 14)
            SubBytes(state);
            ShiftRows(state);
            AddRoundKey(state, expanded_key + 0xe0);
        }
    }

    // Store state into output (transposing back from row-major to column-major)
    output[0]  = state[0];
    output[4]  = state[1];
    output[8]  = state[2];
    output[12] = state[3];
    output[1]  = state[4];
    output[5]  = state[5];
    output[9]  = state[6];
    output[13] = state[7];
    output[2]  = state[8];
    output[6]  = state[9];
    output[10] = state[10];
    output[14] = state[11];
    output[3]  = state[12];
    output[7]  = state[13];
    output[11] = state[14];
    output[15] = state[15];
}