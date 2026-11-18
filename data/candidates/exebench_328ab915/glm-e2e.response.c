int runetochar(char *str, int rune) {
    // Clamp out-of-range code points to the Unicode replacement character (U+FFFD)
    if (rune > 0x10FFFF) {
        rune = 0xFFFD;
    }

    if (rune < 0x80) {
        str[0] = (char)rune;
        return 1;
    } else if (rune < 0x800) {
        str[0] = (char)(0xC0 | (rune >> 6));
        str[1] = (char)(0x80 | (rune & 0x3F));
        return 2;
    } else if (rune < 0x10000) {
        str[0] = (char)(0xE0 | (rune >> 12));
        str[1] = (char)(0x80 | ((rune >> 6) & 0x3F));
        str[2] = (char)(0x80 | (rune & 0x3F));
        return 3;
    } else {
        str[0] = (char)(0xF0 | (rune >> 18));
        str[1] = (char)(0x80 | ((rune >> 12) & 0x3F));
        str[2] = (char)(0x80 | ((rune >> 6) & 0x3F));
        str[3] = (char)(0x80 | (rune & 0x3F));
        return 4;
    }
}