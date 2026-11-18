void poly1305_squeeze(unsigned char *digest, unsigned long long *h) {
    unsigned long long j;
    unsigned int i;

    j = 0;
    for (i = 0; i < 16; i++) {
        j += h[i];
        digest[i] = j & 0xff;
        j >>= 8;
    }
    digest[16] = j & 0x03;
    j >>= 2;
    j *= 5;
    for (i = 0; i < 16; i++) {
        j += digest[i];
        digest[i] = j & 0xff;
        j >>= 8;
    }
    digest[0] += j;
}