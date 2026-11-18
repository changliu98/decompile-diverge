unsigned char utf16_literal_to_utf8(const char *input, const char *end, char **output) {
    unsigned long codepoint = 0;
    int high_surrogate = 0;
    const char *ptr = input;
    unsigned char seq_len = 0;
    unsigned char i = 0;
    unsigned char skip = 0;

    if (end - ptr < 6) {
        return 0;
    }

    high_surrogate = parse_hex4(ptr + 2);

    if (high_surrogate >= 0xDC00 && high_surrogate <= 0xDFFF) {
        return 0;
    }

    if (high_surrogate >= 0xD800 && high_surrogate <= 0xDBFF) {
        const char *low_ptr = ptr + 6;
        int low_surrogate = 0;
        skip = 12;

        if (end - low_ptr < 6) {
            return 0;
        }

        if (low_ptr[0] != '\\' || low_ptr[1] != 'u') {
            return 0;
        }

        low_surrogate = parse_hex4(low_ptr + 2);

        if (low_surrogate < 0xDC00 || low_surrogate > 0xDFFF) {
            return 0;
        }

        codepoint = 0x10000 + (((high_surrogate & 0x3FF) << 10) | (low_surrogate & 0x3FF));
    } else {
        skip = 6;
        codepoint = high_surrogate;
    }

    if (codepoint < 0x80) {
        seq_len = 1;
    } else if (codepoint < 0x800) {
        seq_len = 2;
        skip = 0xC0;
    } else if (codepoint < 0x10000) {
        seq_len = 3;
        skip = 0xE0;
    } else if (codepoint <= 0x10FFFF) {
        seq_len = 4;
        skip = 0xF0;
    } else {
        return 0;
    }

    for (i = seq_len - 1; i > 0; i--) {
        (*output)[i] = (char)((codepoint | 0x80) & 0xBF);
        codepoint >>= 6;
    }

    if (seq_len > 1) {
        (*output)[0] = (char)((codepoint | skip) & 0xFF);
    } else {
        (*output)[0] = (char)(codepoint & 0x7F);
    }

    *output += seq_len;
    return skip;
}