void SubBytes(unsigned char *state) {
    for (int i = 0; i < 16; i++) {
        unsigned char byte = state[i];
        int row = byte >> 4;
        int col = byte & 0xF;
        state[i] = sbox[row][col];
    }
}