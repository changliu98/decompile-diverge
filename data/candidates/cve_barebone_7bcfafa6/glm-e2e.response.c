char* url_canonize2(char *dst, const char *src, size_t len, 
                    unsigned int mask1, unsigned int mask2, unsigned int mask3) {
    size_t i = 0;
    char *ret = NULL;

    // Skip over characters that are already identical in both strings
    while (dst != src) {
        char c = src[i];
        if (c == '\0' || i >= len) {
            break;
        }
        if (c == '%') {
            break;
        }
        dst++;
        i++;
    }

    // Process the remaining characters
    while (1) {
        char c = src[i];
        if (c == '\0' || i >= len) {
            *dst = '\0';
            ret = dst;
            break;
        }

        if (c != '%') {
            // Check if the character is allowed to be unescaped based on bitmasks
            if (mask1 & (1 << (c - 0x21))) {
                *dst = c;
            } else if (c > 0x20 && c < 0x7f) {
                unsigned int allowed = 0;
                if (c < 0x40) {
                    allowed = mask2 & (1 << (0x3f - c));
                } else if (c < 0x60) {
                    allowed = mask3 & (1 << (0x5f - c));
                } else {
                    allowed = mask3 & (1 << (0x7f - c));
                }
                
                if (allowed) {
                    *dst = c;
                } else {
                    *dst = '\0';
                    return dst;
                }
            } else {
                *dst = '\0';
                return dst;
            }
        } else {
            // Handle percent-encoded sequence '%XX'
            char h1 = src[i + 1];
            char h2 = src[i + 2];

            // Validate that both characters are hexadecimal digits
            if (!((h1 >= '0' && h1 <= '9') || (h1 >= 'A' && h1 <= 'F') || (h1 >= 'a' && h1 <= 'f')) ||
                !((h2 >= '0' && h2 <= '9') || (h2 >= 'A' && h2 <= 'F') || (h2 >= 'a' && h2 <= 'f'))) {
                *dst = '\0';
                return dst;
            }

            // Decode the hex values into a single byte
            int v1 = h1;
            int v1_offset = (v1 >= 'a') ? 0x57 : ((v1 >= 'A') ? 0x37 : 0x30);
            int decoded = (v1 - v1_offset) << 4;

            int v2 = h2;
            int v2_offset = (v2 >= 'a') ? 0x57 : ((v2 >= 'A') ? 0x37 : 0x30);
            decoded |= (v2 - v2_offset);
            c = (char)decoded;

            // Check if the decoded character is allowed to be unescaped
            if (c > 0x20 && c < 0x7f) {
                unsigned int allowed = 0;
                if (c < 0x40) {
                    allowed = mask2 & (1 << (0x3f - c));
                } else if (c < 0x60) {
                    allowed = mask3 & (1 << (0x5f - c));
                } else {
                    allowed = mask3 & (1 << (0x7f - c));
                }

                if (!allowed) {
                    // Keep it percent-encoded, but uppercase the hex digits
                    if (h1 >= 'a') h1 -= 0x20;
                    if (h2 >= 'a') h2 -= 0x20;
                    
                    *dst = '%';
                    *(dst + 1) = h1;
                    *(dst + 2) = h2;
                    dst += 2;
                    i += 2;
                } else {
                    *dst = c;
                    i += 2;
                }
            } else {
                // Keep it percent-encoded, but uppercase the hex digits
                if (h1 >= 'a') h1 -= 0x20;
                if (h2 >= 'a') h2 -= 0x20;
                
                *dst = '%';
                *(dst + 1) = h1;
                *(dst + 2) = h2;
                dst += 2;
                i += 2;
            }
        }
        dst++;
        i++;
    }
    return ret;
}