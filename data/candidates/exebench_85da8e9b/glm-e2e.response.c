void unpack_dxt(unsigned char idx, unsigned short c1, unsigned short c0, unsigned char *out) {
    // Unpack color 1 (c1)
    unsigned char r1 = (c1 & 0x1F) << 3;
    unsigned char g1 = (c1 >> 3) & 0xFC;
    unsigned char b1 = (c1 >> 8) & 0xF8; // Equivalent to (c1 >> 11) << 3

    // Unpack color 0 (c0)
    unsigned char r0 = (c0 & 0x1F) << 3;
    unsigned char g0 = (c0 >> 3) & 0xFC;
    unsigned char b0 = (c0 >> 8) & 0xF8; // Equivalent to (c0 >> 11) << 3

    switch (idx) {
        case 0:
            out[0] = r0;
            out[1] = g0;
            out[2] = b0;
            break;
        case 1:
            out[0] = r1;
            out[1] = g1;
            out[2] = b1;
            break;
        case 2:
            if (c0 > c1) {
                // 2 * color0 + color1 / 3
                out[0] = (2 * r0 + r1) / 3;
                out[1] = (2 * g0 + g1) / 3;
                out[2] = (2 * b0 + b1) / 3;
            } else {
                // (color0 + color1) / 2
                out[0] = (r0 + r1) / 2;
                out[1] = (g0 + g1) / 2;
                out[2] = (b0 + b1) / 2;
            }
            break;
        case 3:
            if (c0 > c1) {
                // color0 + 2 * color1 / 3
                out[0] = (r0 + 2 * r1) / 3;
                out[1] = (g0 + 2 * g1) / 3;
                out[2] = (b0 + 2 * b1) / 3;
            } else {
                // Transparent black
                out[0] = 0;
                out[1] = 0;
                out[2] = 0;
            }
            break;
    }
}