int name_len(uint64_t *p, const char *s, const char *end) {
    const char *start = s;
    
    if (s >= end) {
        return -1;
    }

    // Bounds check: 0 <= *p - 1 and s <= *p - 1
    if (*p - 1 > *p - 1 || s > *p - 1) {
        return -1;
    }

    // Check if the first character has the top two bits set (e.g., 0xC0)
    if ((*s & 0xC0) == 0xC0) {
        return 2;
    }

    while (*s != '\0') {
        if (s >= end) {
            return -1;
        }

        // Bounds check: 0 <= *p - 1 and s <= *p - 1
        if (*p - 1 > *p - 1 || s > *p - 1) {
            return -1;
        }

        s++;
    }

    return (int)(s - start + 1);
}