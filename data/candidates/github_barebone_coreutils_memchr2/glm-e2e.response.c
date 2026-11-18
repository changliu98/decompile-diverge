void *memchr2(const void *s, int c1_in, int c2_in, unsigned long n) {
    unsigned char c1 = (unsigned char)c1_in;
    unsigned char c2 = (unsigned char)c2_in;
    void *result = NULL;

    // If both characters are the same, just fallback to standard memchr
    if (c1 == c2) {
        result = memchr(s, c1, n);
        return result;
    }

    const unsigned char *p = (const unsigned char *)s;

    // Unaligned head: process byte-by-byte until pointer is 8-byte aligned
    while (n > 0 && ((unsigned long)p & 0x7) != 0) {
        if (*p == c1 || *p == c2) {
            result = (void *)p;
            return result;
        }
        p++;
        n--;
    }

    // SWAR (SIMD Within A Register) preparation
    unsigned long long magic = 0x0101010101010101ULL;
    
    // Broadcast c1 and c2 to all 8 bytes of a 64-bit integer
    unsigned long long c1_mask = c1 | (c1 << 8);
    c1_mask = c1_mask | (c1_mask << 16);
    c1_mask = c1_mask | (c1_mask << 32);

    unsigned long long c2_mask = c2 | (c2 << 8);
    c2_mask = c2_mask | (c2_mask << 16);
    c2_mask = c2_mask | (c2_mask << 32);

    // The assembly uses a specific trick to compute the high-bit mask (0x80808080...)
    // by doing: (mask << 31) << 1 | mask
    magic = (magic << 31) << 1 | magic;
    c1_mask = (c1_mask << 31) << 1 | c1_mask;
    c2_mask = (c2_mask << 31) << 1 | c2_mask;

    // Main 8-byte aligned loop
    while (n >= 8) {
        unsigned long long chunk = *(unsigned long long *)p;
        unsigned long long v1 = chunk ^ c1_mask;
        unsigned long long v2 = chunk ^ c2_mask;

        // Check for zero bytes using the standard SWAR zero detection trick:
        // ((v - 0x01010101...) & ~v & 0x80808080...)
        unsigned long long match = ((v1 - magic) & ~v1 & magic) | ((v2 - magic) & ~v2 & magic);

        if (match != 0) {
            break; // A match was found in the 8-byte chunk
        }

        p += 8;
        n -= 8;
    }

    // Tail: check remaining bytes individually
    while (n > 0) {
        if (*p == c1 || *p == c2) {
            result = (void *)p;
            return result;
        }
        p++;
        n--;
    }

    result = NULL;
    return result;
}