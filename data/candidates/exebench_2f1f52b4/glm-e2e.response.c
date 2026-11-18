bool isLegalUTF8(const unsigned char *str, int length) {
    const unsigned char *end = str + length;
    unsigned char byte;

    // Equivalent to: if ((unsigned int)(length - 1) > 3) return false;
    if (length < 1 || length > 4) {
        return false;
    }

    // Validate trailing bytes for multi-byte sequences (length 2, 3, or 4)
    if (length > 1) {
        byte = *(--end);
        if (byte < 0x80 || byte > 0xBF) {
            return false;
        }
    }
    if (length > 2) {
        byte = *(--end);
        if (byte < 0x80 || byte > 0xBF) {
            return false;
        }
    }
    if (length > 3) {
        byte = *(--end);
        if (byte > 0xBF) {
            return false;
        }
    }

    // Check the leading byte to prevent overlong sequences and out-of-range code points
    unsigned char first = *str;
    if (first == 0xE0) {
        if (byte < 0xA0) return false; // Prevent overlong 3-byte sequences
    } else if (first == 0xF0) {
        if (byte < 0x90) return false; // Prevent overlong 4-byte sequences
    } else if (first == 0xF4) {
        if (byte > 0x8F) return false; // Prevent code points > U+10FFFF
    } else {
        if (byte < 0x80) return false; // General check for other multi-byte sequences
    }

    // Validate the leading byte itself
    if (*str >= 0x80 && *str < 0xC2) {
        return false; // Continuation byte or overlong 2-byte sequence
    }
    if (*str > 0xF4) {
        return false; // Invalid leading byte
    }

    return true;
}