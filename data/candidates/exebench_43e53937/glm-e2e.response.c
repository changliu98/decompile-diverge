void Utf32toUtf8(unsigned int codepoint, char *out) {
    if (codepoint < 0x80) {
        out[0] = (char)codepoint;
        out[1] = 0;
    } else if (codepoint < 0x800) {
        out[0] = (char)((codepoint >> 6) | 0xC0);
        out[1] = (char)((codepoint & 0x3F) | 0x80);
        out[2] = 0;
    } else if (codepoint < 0x10000) {
        out[0] = (char)((codepoint >> 12) | 0xE0);
        out[1] = (char)(((codepoint >> 6) & 0x3F) | 0x80);
        out[2] = (char)((codepoint & 0x3F) | 0x80);
        out[3] = 0;
    } else if (codepoint < 0x200000) {
        out[0] = (char)((codepoint >> 18) | 0xF0);
        out[1] = (char)(((codepoint >> 12) & 0x3F) | 0x80);
        out[2] = (char)(((codepoint >> 6) & 0x3F) | 0x80);
        out[3] = (char)((codepoint & 0x3F) | 0x80);
        out[4] = 0;
    } else {
        out[0] = '?';
        out[1] = 0;
    }
}