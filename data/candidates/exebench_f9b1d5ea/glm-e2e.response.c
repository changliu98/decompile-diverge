int descape(struct CharInfo *src, struct CharInfo *dst) {
    if (src->c == '\\') {
        switch (src->len) {
            case 'a':  // 0x61 - 0x22 = 0x3F
                dst->len = '\a';
                return 1;
            case 'b':  // 0x62 - 0x22 = 0x40
                dst->len = '\b';
                return 1;
            case 'f':  // 0x66 - 0x22 = 0x44
                dst->len = '\f';
                return 1;
            case 'n':  // 0x6E - 0x22 = 0x4C
                dst->len = '\n';
                return 1;
            case 'r':  // 0x72 - 0x22 = 0x50
                dst->len = '\r';
                return 1;
            case 't':  // 0x74 - 0x22 = 0x52
                dst->len = '\t';
                return 1;
            case 'v':  // 0x76 - 0x22 = 0x54
                dst->len = '\v';
                return 1;
            case '?':  // 0x3F - 0x22 = 0x1D
                dst->len = '\?';
                return 1;
            case '\'': // 0x27 - 0x22 = 0x05
                dst->len = '\'';
                return 1;
            case '"':  // 0x22 - 0x22 = 0x00
                dst->len = '"';
                return 1;
            default:
                break;
        }
    }
    
    dst->c = src->c;
    dst->len = src->len;
    return 0;
}