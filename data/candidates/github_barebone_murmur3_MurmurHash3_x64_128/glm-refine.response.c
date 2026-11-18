void __cdecl MurmurHash3_x64_128(const void *key, const int len, const uint32_t seed, void *out)
{
    const uint64_t c1 = 0x87C37B91114253D5ULL;
    const uint64_t c2 = 0x4CF5AD432745937FULL;
    const uint64_t c3 = 0xFF51AFD7ED558CCDULL;
    const uint64_t c4 = 0xC4CEB9FE1A85EC53ULL;

    const uint8_t *data = (const uint8_t *)key;
    const int nblocks = len / 16;

    uint64_t h1 = seed;
    uint64_t h2 = seed;

    // Process 128-bit blocks
    const uint64_t *blocks = (const uint64_t *)data;
    for (int i = 0; i < nblocks; i++)
    {
        uint64_t k1 = blocks[i * 2];
        uint64_t k2 = blocks[i * 2 + 1];

        k1 *= c1;
        k1 = ROTR64(k1, 31);
        k1 *= c2;
        
        h1 ^= k1;
        h1 = ROTR64(h1, 27);
        h1 = h1 + h2;
        h1 = h1 * 5 + 0x52DCE729; // 1390208809

        k2 *= c2;
        k2 = ROTR64(k2, 33);
        k2 *= c1;
        
        h2 ^= k2;
        h2 = ROTR64(h2, 31);
        h2 = h2 + h1;
        h2 = h2 * 5 + 0x38495AB5; // 944331445
    }

    // Process the tail (up to 15 bytes)
    const uint8_t *tail = data + 16 * nblocks;
    uint64_t k1 = 0;
    uint64_t k2 = 0;

    switch (len & 0xF)
    {
        case 15: k2 ^= (uint64_t)tail[14] << 48; // fallthrough
        case 14: k2 ^= (uint64_t)tail[13] << 40; // fallthrough
        case 13: k2 ^= (uint64_t)tail[12] << 32; // fallthrough
        case 12: k2 ^= (uint64_t)tail[11] << 24; // fallthrough
        case 11: k2 ^= (uint64_t)tail[10] << 16; // fallthrough
        case 10: k2 ^= (uint64_t)tail[9]  << 8;  // fallthrough
        case  9: k2 ^= (uint64_t)tail[8]  << 0;  // fallthrough
                 k2 *= c2;
                 k2 = ROTR64(k2, 33);
                 k2 *= c1;
                 h2 ^= k2;
                 // fallthrough
        case  8: k1 ^= (uint64_t)tail[7] << 56; // fallthrough
        case  7: k1 ^= (uint64_t)tail[6] << 48; // fallthrough
        case  6: k1 ^= (uint64_t)tail[5] << 40; // fallthrough
        case  5: k1 ^= (uint64_t)tail[4] << 32; // fallthrough
        case  4: k1 ^= (uint64_t)tail[3] << 24; // fallthrough
        case  3: k1 ^= (uint64_t)tail[2] << 16; // fallthrough
        case  2: k1 ^= (uint64_t)tail[1] << 8;  // fallthrough
        case  1: k1 ^= (uint64_t)tail[0] << 0;  // fallthrough
                 k1 *= c1;
                 k1 = ROTR64(k1, 31);
                 k1 *= c2;
                 h1 ^= k1;
                 break;
    }

    // Finalization mix
    h1 ^= len;
    h2 ^= len;

    h1 += h2;
    h2 += h1;

    h1 ^= h1 >> 33;
    h1 *= c3;
    h1 ^= h1 >> 33;
    h1 *= c4;
    h1 ^= h1 >> 33;

    h2 ^= h2 >> 33;
    h2 *= c3;
    h2 ^= h2 >> 33;
    h2 *= c4;
    h2 ^= h2 >> 33;

    h1 += h2;
    h2 += h1;

    ((uint64_t *)out)[0] = h1;
    ((uint64_t *)out)[1] = h2;
}