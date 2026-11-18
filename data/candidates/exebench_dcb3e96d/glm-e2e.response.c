int utf8_encode(int32_t cp, char *out) {
    int len = 0;
    
    if (cp >= 0 && cp <= 0x7f) {
        out[0] = (char)(cp & 0x7f);
        len = 1;
    } else if (cp >= 0x80 && cp <= 0x7ff) {
        out[1] = (char)((cp & 0x3f) | 0x80);
        cp >>= 6;
        out[0] = (char)((cp & 0x1f) | 0xc0);
        len = 2;
    } else if (cp >= 0x800 && cp <= 0xffff) {
        out[2] = (char)((cp & 0x3f) | 0x80);
        cp >>= 6;
        out[1] = (char)((cp & 0x3f) | 0x80);
        cp >>= 6;
        out[0] = (char)((cp & 0x0f) | 0xe0);
        len = 3;
    } else if (cp >= 0x10000 && cp <= 0x10ffff) {
        out[3] = (char)((cp & 0x3f) | 0x80);
        cp >>= 6;
        out[2] = (char)((cp & 0x3f) | 0x80);
        cp >>= 6;
        out[1] = (char)((cp & 0x3f) | 0x80);
        cp >>= 6;
        out[0] = (char)((cp & 0x07) | 0xf0);
        len = 4;
    }
    
    out[len] = '\0';
    return len;
}