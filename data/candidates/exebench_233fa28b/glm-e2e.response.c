size_t utf8BytesToCodePoint(const unsigned char *bytes, size_t len, unsigned int *codePoint) {
    if (len == 0) {
        return 0;
    }

    unsigned char firstByte = bytes[0];

    if ((firstByte & 0x80) == 0) {
        *codePoint = firstByte;
        return 1;
    } else if ((firstByte & 0xE0) == 0xC0) {
        if (len < 2) return 0;
        *codePoint = ((firstByte & 0x1F) << 6) | (bytes[1] & 0x3F);
        return 2;
    } else if ((firstByte & 0xF0) == 0xE0) {
        if (len < 3) return 0;
        *codePoint = ((firstByte & 0x0F) << 12) | ((bytes[1] & 0x3F) << 6) | (bytes[2] & 0x3F);
        return 3;
    } else if ((firstByte & 0xF8) == 0xF0) {
        if (len < 4) return 0;
        *codePoint = ((firstByte & 0x07) << 18) | ((bytes[1] & 0x3F) << 12) | ((bytes[2] & 0x3F) << 6) | (bytes[3] & 0x3F);
        return 4;
    }

    return 0;
}