long unicode_to_utf8(char *buf, uint32_t cp) {
    char *p = buf;
    
    if (cp < 0x80) {
        *p++ = (char)cp;
    } else if (cp < 0x800) {
        *p++ = (char)(0xC0 | (cp >> 6));
        *p++ = (char)(0x80 | (cp & 0x3F));
    } else if (cp < 0x10000) {
        *p++ = (char)(0xE0 | (cp >> 12));
        *p++ = (char)(0x80 | ((cp >> 6) & 0x3F));
        *p++ = (char)(0x80 | (cp & 0x3F));
    } else if (cp < 0x200000) {
        *p++ = (char)(0xF0 | (cp >> 18));
        *p++ = (char)(0x80 | ((cp >> 12) & 0x3F));
        *p++ = (char)(0x80 | ((cp >> 6) & 0x3F));
        *p++ = (char)(0x80 | (cp & 0x3F));
    } else if (cp < 0x4000000) {
        *p++ = (char)(0xF8 | (cp >> 24));
        *p++ = (char)(0x80 | ((cp >> 18) & 0x3F));
        *p++ = (char)(0x80 | ((cp >> 12) & 0x3F));
        *p++ = (char)(0x80 | ((cp >> 6) & 0x3F));
        *p++ = (char)(0x80 | (cp & 0x3F));
    } else {
        *p++ = (char)(0xFC | (cp >> 30));
        *p++ = (char)(0x80 | ((cp >> 24) & 0x3F));
        *p++ = (char)(0x80 | ((cp >> 18) & 0x3F));
        *p++ = (char)(0x80 | ((cp >> 12) & 0x3F));
        *p++ = (char)(0x80 | ((cp >> 6) & 0x3F));
        *p++ = (char)(0x80 | (cp & 0x3F));
    }
    
    *p = '\0';
    return p - buf;
}