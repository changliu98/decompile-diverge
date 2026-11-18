int __cdecl read_int(const uint8_t *in, uint32_t *out) {
    uint32_t value = 0;

    // Byte 0
    value |= (in[0] & 0x7F);
    if (in[0] < 0x80) {
        *out = value;
        return 1;
    }

    // Byte 1
    value |= (in[1] & 0x7F) << 7;
    if (in[1] < 0x80) {
        *out = value;
        return 2;
    }

    // Byte 2
    value |= (in[2] & 0x7F) << 14;
    if (in[2] < 0x80) {
        *out = value;
        return 3;
    }

    // Byte 3
    value |= (in[3] & 0x7F) << 21;
    if (in[3] < 0x80) {
        *out = value;
        return 4;
    }

    // Byte 4 (Maximum 5 bytes for a 32-bit integer)
    value |= (in[4] & 0x7F) << 28;
    *out = value;
    return 5;
}