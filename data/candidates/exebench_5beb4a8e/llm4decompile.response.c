void poly1305_squeeze(unsigned char *h, const unsigned long *hr) {
    unsigned long u;
    unsigned int i;

    for (i = 0, u = 0; i < 16; i++) {
        u += hr[i];
        h[i] = u & 0xff;
        u >>= 8;
    }

    u += hr[16];
    h[16] = u & 0x03;
    u >>= 2;
    u *= 5;

    for (i = 0; i < 16; i++) {
        u += h[i];
        h[i] = u & 0xff;
        u >>= 8;
    }

    u += h[16];
    h[16] = u & 0xff;
}