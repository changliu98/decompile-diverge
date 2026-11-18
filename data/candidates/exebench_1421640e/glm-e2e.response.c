void encode_vector(char *out, int y, int x) {
    out[0] = (char)((x >> 5) + 0x20);
    out[1] = (char)((x & 0x1f) + 0x60);
    out[2] = (char)((y >> 5) + 0x20);
    out[3] = (char)((y & 0x1f) + 0x40);
    out[4] = 0;
}