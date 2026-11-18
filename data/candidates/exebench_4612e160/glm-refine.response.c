unsigned int __cdecl utf8_decode_v2(const char *utf8char, size_t size, size_t *charlen)
{
    // Handle empty string or zero size
    if (!size || !*utf8char) {
        if (charlen)
            *charlen = 0;
        return (unsigned int)-1;
    }

    // Standard ASCII character (0xxxxxxx)
    if ((*utf8char & 0x80) == 0) {
        if (charlen)
            *charlen = 1;
        return *utf8char & 0x7F;
    }

    // Multi-byte sequences (11xxxxxx)
    if ((*utf8char & 0xE0) == 0xC0) {
        // 2-byte sequence (110xxxxx 10xxxxxx)
        if (charlen)
            *charlen = 2;
        
        if (size >= 2 && utf8char[1] != '\0') {
            return ((utf8char[0] & 0x1F) << 6) |
                   (utf8char[1] & 0x3F);
        }
    } 
    else if ((*utf8char & 0xF0) == 0xE0) {
        // 3-byte sequence (1110xxxx 10xxxxxx 10xxxxxx)
        if (charlen)
            *charlen = 3;
        
        if (size >= 3 && utf8char[1] != '\0' && utf8char[2] != '\0') {
            return ((utf8char[0] & 0x0F) << 12) |
                   ((utf8char[1] & 0x3F) << 6)  |
                   (utf8char[2] & 0x3F);
        }
    } 
    else if ((*utf8char & 0xF8) == 0xF0) {
        // 4-byte sequence (11110xxx 10xxxxxx 10xxxxxx 10xxxxxx)
        if (charlen)
            *charlen = 4;
        
        if (size >= 4 && utf8char[1] != '\0' && utf8char[2] != '\0' && utf8char[3] != '\0') {
            return ((utf8char[0] & 0x07) << 18) |
                   ((utf8char[1] & 0x3F) << 12) |
                   ((utf8char[2] & 0x3F) << 6)  |
                   (utf8char[3] & 0x3F);
        }
    } 
    else {
        // Invalid UTF-8 leading byte
        if (charlen)
            *charlen = 0;
        return (unsigned int)-1;
    }

    // Reached if a multi-byte sequence was truncated or contained a null byte
    if (charlen)
        *charlen = 0;
    return (unsigned int)-1;
}