uint64_t XXH64_finalize(uint64_t h, const uint8_t *p, uint64_t len, uint32_t seed) {
    len &= 31;

    while (len >= 8) {
        uint64_t k1 = XXH64_round(0, *(const uint64_t *)p, seed);
        h ^= k1;
        h = (h << 27) | (h >> 37); // rol 0x1b
        h = h * 0x9E3779B185EBCA87ULL + 0x85EBCA77C2B2AE63ULL;
        p += 8;
        len -= 8;
    }

    if (len >= 4) {
        h ^= ((uint64_t)(*(const uint32_t *)p) * 0x9E3779B185EBCA87ULL);
        h = (h << 23) | (h >> 41); // rol 0x17
        h = h * 0xC2B2AE3D27D4EB4FULL + 0x165667B19E3779F9ULL;
        p += 4;
        len -= 4;
    }

    while (len > 0) {
        h ^= ((uint64_t)(*p) * 0x27D4EB2F165667C5ULL);
        h = (h << 11) | (h >> 53); // rol 0x0b
        h *= 0x9E3779B185EBCA87ULL;
        p++;
        len--;
    }

    return XXH64_avalanche(h);
}