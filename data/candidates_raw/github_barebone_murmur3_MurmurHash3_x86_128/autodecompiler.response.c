void MurmurHash3_x86_128 ( const void * key, int len, int seed, void * out ) {
    const uint8_t * data = (const uint8_t *)key;
    const int nblocks = len / 16;

    uint32_t h1 = seed;
    uint32_t h2 = seed;
    uint32_t h3 = seed;
    uint32_t h4 = seed;

    uint32_t c1 = 0xcc9e2d51;
    uint32_t c2 = 0x1b873593;
    uint32_t c3 = 0xc62b2795;
    uint32_t c4 = 0x95563b27;

    const uint32_t * blocks = (const uint32_t *)(data + nblocks * 16);

    int i;
    for (i = -nblocks; ; i++) {
        uint32_t k1 = 0;
        uint32_t k2 = 0;
        uint32_t k3 = 0;
        uint32_t k4 = 0;
        if (i != 0) {
            k1 = blocks[4 * i + 0];
            k2 = blocks[4 * i + 1];
            k3 = blocks[4 * i + 2];
            k4 = blocks[4 * i + 3];
        }
        { k1 *= c1; k1 = ((k1 << 15) | (k1 >> (32 - 15))); k1 *= c2; h1 ^= k1; h1 = ((h1 << 19) | (h1 >> (32 - 19))); h1 += h2; h1 = h1 * 5 + 0xe6546b64; };
        { k2 *= c2; k2 = ((k2 << 16) | (k2 >> (32 - 16))); k2 *= c3; h2 ^= k2; h2 = ((h2 << 17) | (h2 >> (32 - 17))); h2 += h3; h2 = h2 * 5 + 0xae554879; };
        { k3 *= c3; k3 = ((k3 << 17) | (k3 >> (32 - 17))); k3 *= c4; h3 ^= k3; h3 = ((h3 << 15) | (h3 >> (32 - 15))); h3 += h4; h3 = h3 * 5 + 0x95563b27; };
        { k4 *= c4; k4 = ((k4 << 18) | (k4 >> (32 - 18))); k4 *= c1; h4 ^= k4; h4 = ((h4 << 13) | (h4 >> (32 - 13))); h4 += h1; h4 = h4 * 5 + 0x74779837; };
        if (i == 0) {
            break;
        }
    }

    const uint8_t * tail = (const uint8_t*)(data + nblocks * 16);

    uint32_t k1 = 0;
    uint32_t k2 = 0;
    uint32_t k3 = 0;
    uint32_t k4 = 0;

    switch (len & 15) {
    case 15:
        k4 ^= tail[14] << 16;
    case 14:
        k4 ^= tail[13] << 8;
    case 13:
        k4 ^= tail[12] << 0;
        k4 *= c4;
        k4 = ((k4 << 18) | (k4 >> (32 - 18)));
        k4 *= c1;
        h4 ^= k4;
    case 12:
        k3 ^= tail[11] << 24;
    case 11:
        k3 ^= tail[10] << 16;
    case 10:
        k3 ^= tail[9] << 8;
    case 9:
        k3 ^= tail[8] << 0;
        k3 *= c3;
        k3 = ((k3 << 17) | (k3 >> (32 - 17)));
        k3 *= c4;
        h3 ^= k3;
    case 8:
        k2 ^= tail[7] << 24;
    case 7:
        k2 ^= tail[6] << 16;
    case 6:
        k2 ^= tail[5] << 8;
    case 5:
        k2 ^= tail[4] << 0;
        k2 *= c2;
        k2 = ((k2 << 16) | (k2 >> (32 - 16)));
        k2 *= c3;
        h2 ^= k2;
    case 4:
        k1 ^= tail[3] << 24;
    case 3:
        k1 ^= tail[2] << 16;
    case 2:
        k1 ^= tail[1] << 8;
    case 1:
        k1 ^= tail[0] << 0;
        k1 *= c1;
        k1 = ((k1 << 15) | (k1 >> (32 - 15)));
        k1 *= c2;
        h1 ^= k1;
    }

    h1 ^= len;
    h2 ^= len;
    h3 ^= len;
    h4 ^= len;

    h1 += h2;
    h1 += h3;
    h1 += h4;
    h2 += h1;
    h3 += h1;
    h4 += h1;

    { h1 ^= h1 >> 16; h1 *= 0x85ebca6b; h1 ^= h1 >> 13; h1 *= 0xc2b2ae35; h1 ^= h1 >> 16; };
    { h2 ^= h2 >> 16; h2 *= 0x85ebca6b; h2 ^= h2 >> 13; h2 *= 0xc2b2ae35; h2 ^= h2 >> 16; };
    { h3 ^= h3 >> 16; h3 *= 0x85ebca6b; h3 ^= h3 >> 13; h3 *= 0xc2b2ae35; h3 ^= h3 >> 16; };
    { h4 ^= h4 >> 16; h4 *= 0x85ebca6b; h4 ^= h4 >> 13; h4 *= 0xc2b2ae35; h4 ^= h4 >> 16; };

    h1 += h2;
    h1 += h3;
    h1 += h4;
    h2 += h1;
    h3 += h1;
    h4 += h1;

    uint32_t * hashes = (uint32_t *)out;
    hashes[0] = h1;
    hashes[1] = h2;
    hashes[2] = h3;
    hashes[3] = h4;
}