void __cdecl utf8_int_string(unsigned int unicode_value, char *string)
{
    // Guard against NULL pointer dereference
    if (string == NULL) {
        return;
    }

    // 1-byte sequence: U+0000 to U+007F
    if (unicode_value <= 0x7F) {
        string[0] = (char)unicode_value;
        string[1] = '\0';
    }
    // 2-byte sequence: U+0080 to U+07FF
    else if (unicode_value <= 0x7FF) {
        string[0] = (char)((unicode_value >> 6) | 0xC0);
        string[1] = (char)((unicode_value & 0x3F) | 0x80);
        string[2] = '\0';
    }
    // 3-byte sequence: U+0800 to U+FFFF
    else if (unicode_value <= 0xFFFF) {
        string[0] = (char)((unicode_value >> 12) | 0xE0);
        string[1] = (char)(((unicode_value >> 6) & 0x3F) | 0x80);
        string[2] = (char)((unicode_value & 0x3F) | 0x80);
        string[3] = '\0';
    }
    // 4-byte sequence: U+10000 to U+1FFFFF
    else if (unicode_value <= 0x1FFFFF) {
        string[0] = (char)((unicode_value >> 18) | 0xF0);
        string[1] = (char)(((unicode_value >> 12) & 0x3F) | 0x80);
        string[2] = (char)(((unicode_value >> 6) & 0x3F) | 0x80);
        string[3] = (char)((unicode_value & 0x3F) | 0x80);
        string[4] = '\0';
    }
    // Fallback for invalid code points (> U+1FFFFF)
    else {
        // Matches the implicit behavior of the original nested conditions
        string[0] = '\0';
    }
}