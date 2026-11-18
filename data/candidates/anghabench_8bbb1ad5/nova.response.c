static void RewindBitPosition(size_t bit, unsigned char **out, size_t *out_len) {
    size_t byte = bit / 8;
    size_t mask = ~(((size_t)1 << (bit & 7)) - 1);
    (*out_len) = byte;
    (*out)[byte] &= mask;
}