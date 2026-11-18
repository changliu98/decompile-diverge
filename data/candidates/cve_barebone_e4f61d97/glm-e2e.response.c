char* url_canonize2(char *dst, const char *src, size_t len, unsigned int flags, unsigned int lower_flags, unsigned int upper_flags, unsigned int other_flags) {
    size_t i = 0;

    // Skip leading characters that are already identical
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

    // Process the rest of the string
    while (1) {
        char c = src[i];
        if (c == '\0' || i >= len) {
            *dst = '\0';
            return dst;
        }

        if (c == '%') {
            char h1 = src[i + 1];
            if (h1 == '\0') {
                *dst = '\0';
                return dst;
            }
            char h2 = src[i + 2];

            // Check if both characters are valid hexadecimal digits
            if (!((h1 >= '0' && h1 <= '9') || (h1 >= 'A' && h1 <= 'F') || (h1 >= 'a' && h1 <= 'f')) ||
                !((h2 >= '0' && h2 <= '9') || (h2 >= 'A' && h2 <= 'F') || (h2 >= 'a' && h2 <= 'f'))) {
                *dst = '\0';
                return dst;
            }

            // Convert hex characters to a character value
            int v1 = (h1 >= 'a') ? (h1 - 'a' + 10) : ((h1 >= 'A') ? (h1 - 'A' + 10) : (h1 - '0'));
            int v2 = (h2 >= 'a') ? (h2 - 'a' + 10) : ((h2 >= 'A') ? (h2 - 'A' + 10) : (h2 - '0'));
            char decoded = (v1 << 4) | v2;

            // Check if the decoded character is printable and not flagged for re-encoding
            if (decoded > 0x20 && decoded < 0x7f) {
                unsigned int mask = 0;
                if (decoded < 0x40) {
                    mask = lower_flags;
                } else if (decoded < 0x60) {
                    mask = upper_flags;
                } else {
                    mask = other_flags;
                }

                if ((mask & (1 << (0x7f - decoded))) == 0) {
                    *dst = decoded;
                    i += 2;
                    goto next_char;
                }
            }

            // If it needs to remain percent-encoded, uppercase the hex digits
            if (h1 >= 'a') h1 -= 32;
            if (h2 >= 'a') h2 -= 32;

            *dst = '%';
            *(dst + 1) = h1;
            *(dst + 2) = h2;
            dst += 2;
            i += 2;
        } else {
            // Check if the character is flagged for mandatory percent-encoding
            if ((flags & (1 << (c - 0x21))) != 0) {
                *dst = '\0';
                return dst;
            }

            // Check if the character is printable and not flagged for percent-encoding
            if (c > 0x20 && c < 0x7f) {
                unsigned int mask = 0;
                if (c < 0x40) {
                    mask = lower_flags;
                } else if (c < 0x60) {
                    mask = upper_flags;
                } else {
                    mask = other_flags;
                }

                if ((mask & (1 << (0x7f - c))) != 0) {
                    *dst = '\0';
                    return dst;
                }
            }

            *dst = c;
        }

    next_char:
        dst++;
        i++;
    }
}