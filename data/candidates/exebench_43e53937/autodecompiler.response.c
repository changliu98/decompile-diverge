void Utf32toUtf8(unsigned int codepoint, char * utf8) {
    if (codepoint <= 0x80) {
        utf8[0] = (char)codepoint;
        utf8[1] = '\0';
        return;
    }
    else if (codepoint < 0x800) {
        utf8[0] = (char)(0xC0 | (codepoint >> 6));
        utf8[1] = (char)(0x80 | (codepoint & 0x3F));
        utf8[2] = '\0';
        return;
    }
    else if (codepoint < 0x10000) {
        utf8[0] = (char)(0xE0 | (codepoint >> 12));
        utf8[1] = (char)(0x80 | ((codepoint >> 6) & 0x3F));
        utf8[2] = (char)(0x80 | (codepoint & 0x3F));
        utf8[3] = '\0';
        return;
    }
    else if (codepoint < 0x200000) {
        utf8[0] = (char)(0xF0 | (codepoint >> 18));
        utf8[1] = (char)(0x80 | ((codepoint >> 12) & 0x3F));
        utf8[2] = (char)(0x80 | ((codepoint >> 6) & 0x3F));
        utf8[3] = (char)(0x80 | (codepoint & 0x3F));
        utf8[4] = '\0';
        return;
    }
    else {
        utf8[0] = '?';
        utf8[1] = '\0';
    }
}