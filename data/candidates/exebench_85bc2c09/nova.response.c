void yxyDES2_Int2Bits(int n, char *s) {
    unsigned int i = 0;
    for (i = 0; i < sizeof(n) * 8; i++) {
        s[i] = (n << i) & 0x80? 1 : 0;
    }
}