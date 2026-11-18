int genx(char *out, const char *in) {
    int ret = 0;
    short map[256];

    // Initialize map with -1 (0xFFFF for a signed short)
    for (int i = 0; i < 256; i++) {
        map[i] = -1;
    }

    // Map characters to their first seen index
    for (int i = 0; i < 256; i++) {
        unsigned char c = in[i];
        short val = map[c];
        if (val != -1) {
            ret = 1;
        } else {
            map[c] = (short)i;
        }
    }

    // Write mapped values to output buffer
    for (int i = 0; i < 256; i++) {
        out[i] = (char)map[i];
    }

    // Return -1 if ret is 1, otherwise 0
    return ret ? -1 : 0;
}