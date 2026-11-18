void func0(int codepoint, char *utf8) {
    int size = 0;

    if (codepoint >= 0 && codepoint < 0x80) {
        utf8[size++] = codepoint & 0x7F;
    } else if (codepoint >= 0x80 && codepoint < 0x800) {
        utf8[size++] = 0xC0 | (codepoint >> 6);
        utf8[size++] = 0x80 | (codepoint & 0x3F);
    } else if (codepoint >= 0x800 && codepoint < 0x10000) {
        utf8[size++] = 0xE0 | (codepoint >> 12);
        utf8[size++] = 0x80 | ((codepoint >> 6) & 0x3F);
        utf8[size++] = 0x80 | (codepoint & 0x3F);
    } else if (codepoint >= 0x10000 && codepoint < 0x110000) {
        utf8[size++] = 0xF0 | (codepoint >> 18);
        utf8[size++] = 0x80 | ((codepoint >> 12) & 0x3F);
        utf8[size++] = 0x80 | ((codepoint >> 6) & 0x3F);
        utf8[size++] = 0x80 | (codepoint & 0x3F);
    } else {
        utf8[size++] = '\0';
    }

    utf8[size] = '\0';
}