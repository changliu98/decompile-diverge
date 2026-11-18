void yxyDES2_Int2Bits(int val, char *bits) {
    for (int i = 0; i < 4; i++) {
        bits[i] = (val << i) & 0x8 >> 3;
    }
}