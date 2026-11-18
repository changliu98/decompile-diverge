void poly1305_squeeze(uint8_t *out, uint64_t *h) {
    uint64_t f = 0;
    int i;

    // First loop: squeeze out the first 16 bytes
    for (i = 0; i < 16; i++) {
        f += h[i];
        out[i] = (uint8_t)(f & 0xff);
        f >>= 8;
    }

    // Process the 17th byte (index 16)
    f += h[16];
    out[16] = (uint8_t)(f & 0x3);
    f >>= 2;
    f = (f << 2) + f; // Equivalent to f *= 5

    // Second loop: add the carry back into the first 16 bytes
    for (i = 0; i < 16; i++) {
        f += out[i];
        out[i] = (uint8_t)(f & 0xff);
        f >>= 8;
    }

    // Final carry added to the 17th byte
    out[16] += (uint8_t)f;
}