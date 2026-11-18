int read_int(const uint8_t *in, uint32_t *val) {
    // Byte 0
    *val = in[0] & 0x7F;
    if (in[0] < 0x80) {
        return 1;
    }

    // Byte 1
    *val |= (in[1] & 0x7F) << 7;
    if (in[1] < 0x80) {
        return 2;
    }

    // Byte 2
    *val |= (in[2] & 0x7F) << 14;
    if (in[2] < 0x80) {
        return 3;
    }

    // Byte 3
    *val |= (in[3] & 0x7F) << 21;
    if (in[3] < 0x80) {
        return 4;
    }

    // Byte 4
    *val |= (in[4] & 0x7F) << 28;
    return 5;
}