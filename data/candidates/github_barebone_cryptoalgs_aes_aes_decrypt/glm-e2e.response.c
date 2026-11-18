void aes_decrypt(const uint8_t *in, uint8_t *out, const uint8_t *round_keys, int key_size) {
    uint8_t state[16];

    // Load input block into state matrix (transposed to column-major)
    state[0]  = in[0];
    state[4]  = in[1];
    state[8]  = in[2];
    state[12] = in[3];
    state[1]  = in[4];
    state[5]  = in[5];
    state[9]  = in[6];
    state[13] = in[7];
    state[2]  = in[8];
    state[6]  = in[9];
    state[10] = in[10];
    state[14] = in[11];
    state[3]  = in[12];
    state[7]  = in[13];
    state[11] = in[14];
    state[15] = in[15];

    // Initial AddRoundKey for round Nr
    if (key_size > 0x80) {
        if (key_size > 0xc0) {
            // AES-256 (Nr = 14)
            AddRoundKey(state, round_keys + 0xe0);
            InvShiftRows(state);
            InvSubBytes(state);
            AddRoundKey(state, round_keys + 0xd0);
            InvMixColumns(state);
            InvShiftRows(state);
            InvSubBytes(state);
            AddRoundKey(state, round_keys + 0xc0);
            InvMixColumns(state);
        } else {
            // AES-192 (Nr = 12)
            AddRoundKey(state, round_keys + 0xc0);
        }
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state, round_keys + 0xb0);
        InvMixColumns(state);
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state, round_keys + 0xa0);
        InvMixColumns(state);
    } else {
        // AES-128 (Nr = 10)
        AddRoundKey(state, round_keys + 0xa0);
    }

    // Rounds 9 down to 1 (unrolled)
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, round_keys + 0x90);
    InvMixColumns(state);

    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, round_keys + 0x80);
    InvMixColumns(state);

    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, round_keys + 0x70);
    InvMixColumns(state);

    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, round_keys + 0x60);
    InvMixColumns(state);

    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, round_keys + 0x50);
    InvMixColumns(state);

    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, round_keys + 0x40);
    InvMixColumns(state);

    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, round_keys + 0x30);
    InvMixColumns(state);

    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, round_keys + 0x20);
    InvMixColumns(state);

    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, round_keys + 0x10);
    InvMixColumns(state);

    // Final round (Round 0)
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, round_keys);

    // Store state matrix into output block (transposed back to row-major)
    out[0]  = state[0];
    out[1]  = state[4];
    out[2]  = state[8];
    out[3]  = state[12];
    out[4]  = state[1];
    out[5]  = state[5];
    out[6]  = state[9];
    out[7]  = state[13];
    out[8]  = state[2];
    out[9]  = state[6];
    out[10] = state[10];
    out[11] = state[14];
    out[12] = state[3];
    out[13] = state[7];
    out[14] = state[11];
    out[15] = state[15];
}