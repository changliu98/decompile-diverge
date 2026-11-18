int unicoder_utf16_decode(uint32_t *out, const uint8_t *in, int endian) {
    uint32_t c1;
    uint32_t c2;
    uint32_t lo;
    uint32_t hi;

    if (endian != 2 && endian != 1) {
        return -4;
    }
    if (in == 0) {
        return -1;
    }
    if (out == 0) {
        return -1;
    }

    if (endian == 1) {
        c1 = ((uint32_t)in[1] << 8) | in[0];
        c2 = ((uint32_t)in[3] << 8) | in[2];
    } else {
        c1 = ((uint32_t)in[0] << 8) | in[1];
        c2 = ((uint32_t)in[2] << 8) | in[3];
    }

    if (c1 < 0xd800 || c1 > 0xdfff) {
        if (c1 > 0x10ffff) {
            return -16;
        }
        *out = c1;
        return 2;
    }

    if (c1 < 0xd800 || c1 > 0xdbff || c2 < 0xdc00 || c2 > 0xdfff) {
        return -8;
    }

    hi = c1 & 0x3ff;
    lo = c2 & 0x3ff;
    *out = 0;
    *out |= hi;
    *out = *out << 10;
    *out |= lo;
    *out = *out + 0x10000;

    return 4;
}