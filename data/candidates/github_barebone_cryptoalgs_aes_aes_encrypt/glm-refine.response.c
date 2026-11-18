void __cdecl aes_encrypt(const BYTE *in, BYTE *out, const WORD *key, int keysize)
{
    BYTE state[4][4];
    int Nr; // Number of rounds
    int i;

    // Determine the total number of rounds based on key size
    if (keysize == 128) {
        Nr = 10;
    } else if (keysize == 192) {
        Nr = 12;
    } else {
        Nr = 14;
    }

    // Copy input bytes into the AES state matrix (column-major order)
    memcpy(state, in, 16);

    // Initial round key addition
    AddRoundKey(state, key);

    // Perform rounds 1 to Nr-1
    for (i = 1; i < Nr; i++) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, key + 4 * i);
    }

    // Final round (MixColumns is omitted)
    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, key + 4 * Nr);

    // Copy state matrix back to the output buffer
    memcpy(out, state, 16);
}