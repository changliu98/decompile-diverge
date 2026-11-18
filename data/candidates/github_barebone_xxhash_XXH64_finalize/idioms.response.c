unsigned long XXH64_finalize(void *input, unsigned long len, unsigned long seed)
{
    unsigned long total_len = len;
    unsigned long hash = seed;
    unsigned long *ptr64 = (const uint64_t*)input;
    unsigned long *end64 = ptr64 + (len / 8);
    unsigned char *ptr = (const uint8_t*)input;
    unsigned char *end = ptr + len;
    unsigned int *ptr32 = (const uint32_t*)input;
    unsigned int *end32 = ptr32 + (len / 4);
    unsigned long k1 = 0;
    unsigned long k2 = XXH_align64(ptr, XXH_unaligned);
    while (ptr64 < end64)
    {
        hash ^= XXH64_round(k1, k2);
        hash = (hash << 27) | (hash >> (64 - 27));
        hash += k1;
        hash += k2;
        k1 = k2;
        k2 = *ptr64++;
    }
    ptr = (unsigned char *)ptr64;
    end = (unsigned char *)end64;
    if (ptr32 < end32)
    {
        hash ^= XXH32_round(k1, k2);
        hash = (hash << 23) | (hash >> (32 - 23));
        hash += k1;
        hash += k2;
        ptr = (unsigned char *)++end32;
        end = (unsigned char *)end;
        k1 = k2;
        k2 = *ptr32++;
    }
    while (ptr < end)
    {
        hash ^= (uint64_t)(unsigned int)(k1 * 2654435761UL) * (unsigned int)(k2 * 2654435761UL);
        hash = (hash << 11) | (hash >> (64 - 11));
        hash += k1 + k2;
        k1 = k2;
        k2 = *ptr++;
    }
    hash ^= k1;
    hash ^= k2;
    hash ^= total_len;
    hash = (hash << 33) | (hash >> (64 - 33));
    hash *= 0xff51afd7ed558ccDLL;
    hash = (hash << 33) | (hash >> (64 - 33));
    hash += seed;
    return (XXH_hash_t)(hash);
}