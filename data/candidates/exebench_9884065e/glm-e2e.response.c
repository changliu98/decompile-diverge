const char *_PL__utf8_get_char(const char *s, int *c) {
    const char *next;
    
    // 2-byte sequence: 110xxxxx 10xxxxxx
    if ((s[0] & 0xE0) == 0xC0 && (s[1] & 0xC0) == 0x80) {
        *c = ((s[0] & 0x1F) << 6) | (s[1] & 0x3F);
        next = s + 2;
    }
    // 3-byte sequence: 1110xxxx 10xxxxxx 10xxxxxx
    else if ((s[0] & 0xF0) == 0xE0 && (s[1] & 0xC0) == 0x80 && (s[2] & 0xC0) == 0x80) {
        *c = ((s[0] & 0x0F) << 12) | ((s[1] & 0x3F) << 6) | (s[2] & 0x3F);
        next = s + 3;
    }
    // 4-byte sequence: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    else if ((s[0] & 0xF8) == 0xF0 && (s[1] & 0xC0) == 0x80 && 
             (s[2] & 0xC0) == 0x80 && (s[3] & 0xC0) == 0x80) {
        *c = ((s[0] & 0x07) << 18) | ((s[1] & 0x3F) << 12) | 
             ((s[2] & 0x3F) << 6)  |  (s[3] & 0x3F);
        next = s + 4;
    }
    // 5-byte sequence: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
    else if ((s[0] & 0xFC) == 0xF8 && (s[1] & 0xC0) == 0x80 && 
             (s[2] & 0xC0) == 0x80 && (s[3] & 0xC0) == 0x80 && 
             (s[4] & 0xC0) == 0x80) {
        *c = ((s[0] & 0x03) << 24) | ((s[1] & 0x3F) << 18) | 
             ((s[2] & 0x3F) << 12) | ((s[3] & 0x3F) << 6)  | 
              (s[4] & 0x3F);
        next = s + 5;
    }
    // 6-byte sequence: 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
    else if ((s[0] & 0xFE) == 0xFC && (s[1] & 0xC0) == 0x80 && 
             (s[2] & 0xC0) == 0x80 && (s[3] & 0xC0) == 0x80 && 
             (s[4] & 0xC0) == 0x80 && (s[5] & 0xC0) == 0x80) {
        *c = ((s[0] & 0x01) << 30) | ((s[1] & 0x3F) << 24) | 
             ((s[2] & 0x3F) << 18) | ((s[3] & 0x3F) << 12) | 
             ((s[4] & 0x3F) << 6)  |  (s[5] & 0x3F);
        next = s + 6;
    }
    // 1-byte sequence: 0xxxxxxx
    else {
        *c = s[0] & 0xFF;
        next = s + 1;
    }
    
    return next;
}