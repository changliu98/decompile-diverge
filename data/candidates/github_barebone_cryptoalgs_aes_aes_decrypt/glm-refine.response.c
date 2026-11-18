void __cdecl aes_decrypt(const BYTE *in, BYTE *out, const WORD *key, int keysize)
{
    BYTE state[4][4];

    // Load input bytes into the AES state matrix (column-major order)
    for (int i = 0; i < 16; i++) {
        state[i % 4][i / 4] = in[i];
    }

    // Initial AddRoundKey based on key size
    if (keysize < 192) {
        // AES-128 (Round key 10)
        AddRoundKey(state, key + 40);
    } else {
        if (keysize < 256) {
            // AES-192 (Round key 12)
            AddRoundKey(state, key + 48);
        } else {
            // AES-256 (Round keys 14 and 13)
            AddRoundKey(state, key + 56);
            InvShiftRows(state);
            InvSubBytes(state);
            AddRoundKey(state, key + 52);
            InvMixColumns(state);
            InvShiftRows(state);
            InvSubBytes(state);
            AddRoundKey(state, key + 48);
            InvMixColumns(state);
        }
        // Common rounds for AES-192 and AES-256 (Round keys 11 and 10)
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state, key + 44);
        InvMixColumns(state);
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state, key + 40);
        InvMixColumns(state);
    }

    // Common rounds for all key sizes (Round keys 9 down to 1)
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, key + 36);
    InvMixColumns(state);
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, key + 32);
    InvMixColumns(state);
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, key + 28);
    InvMixColumns(state);
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, key + 24);
    InvMixColumns(state);
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, key + 20);
    InvMixColumns(state);
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, key + 16);
    InvMixColumns(state);
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, key + 12);
    InvMixColumns(state);
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, key + 8);
    InvMixColumns(state);
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, key + 4);
    InvMixColumns(state);

    // Final round (Round key 0)
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, key);

    // Unload state matrix into output bytes (column-major order)
    for (int i = 0; i < 16; i++) {
        out[i] = state[i % 4][i / 4];
    }
}