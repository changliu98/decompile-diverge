void poly1305_add(unsigned char *a, unsigned char *b) {
    unsigned short int c = 0;
    for (int i = 0; i < N; i++) {
        c += a[i] + b[i];
        a[i] = c & 0xFF;
        c >>= 8;
    }
}