int unicoder_utf32_decode(uint32_t *out, const uint8_t *in, int endian) {
    uint32_t code_point = 0;
    int i;

    // Check for valid endianness (1 = little, 2 = big)
    if (endian != 1 && endian != 2) {
        return -4;
    }

    // Check for null pointers
    if (in == 0) {
        return -1;
    }
    if (out == 0) {
        return -1;
    }

    // Decode the 4 bytes into a 32-bit code point
    for (i = 0; i < 4; i++) {
        if (endian == 2) { // Big Endian
            if (i > 0) {
                code_point <<= 8;
            }
            code_point |= in[i];
        } else { // Little Endian (endian == 1)
            if (i > 0) {
                code_point >>= 8;
            }
            code_point |= ((uint32_t)in[i]) << 24;
        }
    }

    // Check if the code point is within the valid Unicode range
    if (code_point > 0x10FFFF) {
        return -16;
    }

    // Check for UTF-16 surrogate pairs (reserved range in UTF-32)
    if (code_point >= 0xD800 && code_point <= 0xDFFF) {
        return -16;
    }

    // Store the result and return the number of bytes consumed
    *out = code_point;
    return 4;
}