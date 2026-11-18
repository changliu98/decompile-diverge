void aes_encrypt(unsigned char *in, unsigned char *out, unsigned long *rk, int keysize)
{
    unsigned long state[4];

    state[0] = ((unsigned long)(in)[0] ) | ((unsigned long)(in)[1] << 8) |
               ((unsigned long)(in)[2] << 16) | ((unsigned long)(in)[3] << 24);
    state[1] = ((unsigned long)(in + 4)[0] ) | ((unsigned long)(in + 4)[1] << 8) |
               ((unsigned long)(in + 4)[2] << 16) | ((unsigned long)(in + 4)[3] << 24);
    state[2] = ((unsigned long)(in + 8)[0] ) | ((unsigned long)(in + 8)[1] << 8) |
               ((unsigned long)(in + 8)[2] << 16) | ((unsigned long)(in + 8)[3] << 24);
    state[3] = ((unsigned long)(in + 12)[0] ) | ((unsigned long)(in + 12)[1] << 8) |
               ((unsigned long)(in + 12)[2] << 16) | ((unsigned long)(in + 12)[3] << 24);

    AddRoundKey(state, rk);
    SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state, rk + 4);
    SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state, rk + 8);
    SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state, rk + 12);
    SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state, rk + 16);
    SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state, rk + 20);
    SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state, rk + 24);
    SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state, rk + 28);
    if (keysize != 128) {
        SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state, rk + 32);
        SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state, rk + 36);
        if (keysize != 192) {
            SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state, rk + 40);
            SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state, rk + 44);
            SubBytes(state); ShiftRows(state); AddRoundKey(state, rk + 48);
        } else {
            SubBytes(state); ShiftRows(state); AddRoundKey(state, rk + 40);
        }
    } else {
        SubBytes(state); ShiftRows(state); AddRoundKey(state, rk + 40);
    }

    do { (out)[0] = (state[0]); (out)[1] = (state[0]) >> 8; (out)[2] = (state[0]) >> 16; (out)[3] = (state[0]) >> 24; } while (0);
    do { (out + 4)[0] = (state[1]); (out + 4)[1] = (state[1]) >> 8; (out + 4)[2] = (state[1]) >> 16; (out + 4)[3] = (state[1]) >> 24; } while (0);
    do { (out + 8)[0] = (state[2]); (out + 8)[1] = (state[2]) >> 8; (out + 8)[2] = (state[2]) >> 16; (out + 8)[3] = (state[2]) >> 24; } while (0);
    do { (out + 12)[0] = (state[3]); (out + 12)[1] = (state[3]) >> 8; (out + 12)[2] = (state[3]) >> 16; (out + 12)[3] = (state[3]) >> 24; } while (0);
}