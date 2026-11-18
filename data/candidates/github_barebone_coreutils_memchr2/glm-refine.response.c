void *memchr2(const void *s, int c1_in, int c2_in, size_t n)
{
    uint8_t c1 = (uint8_t)c1_in;
    uint8_t c2 = (uint8_t)c2_in;
    size_t remaining = n;

    // If both characters are the same, fall back to standard memchr
    if (c1 == c2)
        return memchr(s, c1, n);

    const uint8_t *byte_ptr = (const uint8_t *)s;

    // 1. Align the pointer to an 8-byte boundary.
    // Checking bytes one by one until we reach an 8-byte aligned address.
    while (remaining > 0 && (PTR_TO_UINT64(byte_ptr) & 7) != 0)
    {
        if (*byte_ptr == c1 || *byte_ptr == c2)
            return (void *)byte_ptr;
        
        byte_ptr++;
        remaining--;
    }

    // 2. Prepare the SWAR magic constants.
    // We duplicate the target bytes across all 8 bytes of a 64-bit integer.
    const uint64_t LO_MAGIC = 0x0101010101010101ULL;
    const uint64_t HI_MAGIC = 0x8080808080808080ULL;

    uint64_t c1_16 = (c1 << 8) | c1;
    uint64_t c2_16 = (c2 << 8) | c2;

    uint64_t c1_32 = (c1_16 << 16) | c1_16;
    uint64_t c2_32 = (c2_16 << 16) | c2_16;

    uint64_t repeated_c1 = (c1_32 << 32) | c1_32;
    uint64_t repeated_c2 = (c2_32 << 32) | c2_32;

    const uint64_t *longword_ptr = (const uint64_t *)byte_ptr;

    // 3. Process 8 bytes at a time.
    // The bitwise trick `(X ^ repeated_c) - LO_MAGIC` will have its high bit set
    // in any byte where X == repeated_c. We OR the results for c1 and c2.
    while (remaining >= 8)
    {
        uint64_t current_word = *longword_ptr;
        
        uint64_t match_c1 = (repeated_c1 ^ current_word);
        uint64_t match_c2 = (repeated_c2 ^ current_word);
        
        uint64_t has_zero_byte = (~(match_c1) & (match_c1 - LO_MAGIC)) | 
                                 (~(match_c2) & (match_c2 - LO_MAGIC));
        
        if ((has_zero_byte & HI_MAGIC) != 0)
            break; // Found a match within the 8 bytes

        longword_ptr++;
        remaining -= 8;
    }

    // 4. Check the remaining bytes (or the bytes inside the matched block) one by one.
    const uint8_t *final_ptr = (const uint8_t *)longword_ptr;
    while (remaining > 0)
    {
        if (*final_ptr == c1 || *final_ptr == c2)
            return (void *)final_ptr;
        
        final_ptr++;
        remaining--;
    }

    return NULL;
}