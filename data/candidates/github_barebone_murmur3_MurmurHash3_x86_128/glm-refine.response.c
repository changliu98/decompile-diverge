void __cdecl MurmurHash3_x86_128(const void *key, const int len, uint32_t seed, void *out)
{
    const uint8_t *data = (const uint8_t *)key;
    const int nblocks = len / 16;

    uint32_t h1 = seed;
    uint32_t h2 = seed;
    uint32_t h3 = seed;
    uint32_t h4 = seed;

    const uint32_t *blocks = (const uint32_t *)(data + nblocks * 16);

    // Body
    for (int i = -nblocks; i; ++i)
    {
        uint32_t k1 = blocks[4 * i + 0];
        uint32_t k2 = blocks[4 * i + 1];
        uint32_t k3 = blocks[4 * i + 2];
        uint32_t k4 = blocks[4 * i + 3];

        // Inverse constants used by the decompiler:
        // 597399067  = inverse of 0xCC9E2D51
        // -1425107063 = inverse of 0x1B873593
        // 951274213  = inverse of 0x85EBCA6B
        // -1578923117 = inverse of 0xC2B2AE35

        k1 = 597399067 * k1;
        k1 = ROTL32(k1, 15);
        k1 *= -1425107063;
        h1 ^= k1;
        h1 = ROTL32(h1, 19);
        h1 += h2;
        h1 = h1 * 5 + 1444728091;

        k2 = -1425107063 * k2;
        k2 = ROTL32(k2, 16);
        k2 *= 951274213;
        h2 ^= k2;
        h2 = ROTL32(h2, 17);
        h2 += h3;
        h2 = h2 * 5 + 197830471;

        k3 = 951274213 * k3;
        k3 = ROTL32(k3, 17);
        k3 *= -1578923117;
        h3 ^= k3;
        h3 = ROTL32(h3, 15);
        h3 += h4;
        h3 = h3 * 5 - 1764942795;

        k4 = -1578923117 * k4;
        k4 = ROTL32(k4, 18);
        k4 *= 597399067;
        h4 ^= k4;
        h4 = ROTL32(h4, 13);
        h4 += h1;
        h4 = h4 * 5 + 850148119;
    }

    // Tail
    const uint8_t *tail = (const uint8_t *)(data + nblocks * 16);
    uint32_t k1 = 0;
    uint32_t k2 = 0;
    uint32_t k3 = 0;
    uint32_t k4 = 0;

    switch (len & 0xF)
    {
        case 15:
            k4 ^= tail[14] << 16;
        case 14:
            k4 ^= tail[13] << 8;
        case 13:
            k4 ^= tail[12];
            k4 = 951274213 * k4;
            k4 = ROTL32(k4, 18);
            k4 *= 597399067;
            h4 ^= k4;
        case 12:
            k3 ^= tail[11] << 24;
        case 11:
            k3 ^= tail[10] << 16;
        case 10:
            k3 ^= tail[9] << 8;
        case 9:
            k3 ^= tail[8];
            k3 = -1425107063 * k3;
            k3 = ROTL32(k3, 17);
            k3 *= -1578923117;
            h3 ^= k3;
        case 8:
            k2 ^= tail[7] << 24;
        case 7:
            k2 ^= tail[6] << 16;
        case 6:
            k2 ^= tail[5] << 8;
        case 5:
            k2 ^= tail[4];
            k2 = 597399067 * k2;
            k2 = ROTL32(k2, 16);
            k2 *= 951274213;
            h2 ^= k2;
        case 4:
            k1 ^= tail[3] << 24;
        case 3:
            k1 ^= tail[2] << 16;
        case 2:
            k1 ^= tail[1] << 8;
        case 1:
            k1 ^= tail[0];
            k1 = 597399067 * k1;
            k1 = ROTL32(k1, 15);
            k1 *= -1425107063;
            h1 ^= k1;
    }

    // Finalization
    h1 ^= len;
    h2 ^= len;
    h3 ^= len;
    h4 ^= len;

    h1 += h2 + h3 + h4;
    h2 += h1;
    h3 += h1;
    h4 += h1;

    // fmix32
    uint32_t v1 = h1;
    v1 ^= v1 >> 16;
    v1 *= -2048144789; // 0x85EBCA6B
    v1 ^= v1 >> 13;
    v1 *= -1028477387; // 0xC2B2AE35
    v1 ^= v1 >> 16;

    uint32_t v2 = h2;
    v2 ^= v2 >> 16;
    v2 *= -2048144789;
    v2 ^= v2 >> 13;
    v2 *= -1028477387;
    v2 ^= v2 >> 16;

    uint32_t v3 = h3;
    v3 ^= v3 >> 16;
    v3 *= -2048144789;
    v3 ^= v3 >> 13;
    v3 *= -1028477387;
    v3 ^= v3 >> 16;

    uint32_t v4 = h4;
    v4 ^= v4 >> 16;
    v4 *= -2048144789;
    v4 ^= v4 >> 13;
    v4 *= -1028477387;
    v4 ^= v4 >> 16;

    h1 = v1 + v2 + v3 + v4;
    h2 = v2 + h1;
    h3 = v3 + h1;
    h4 = v4 + h1;

    ((uint32_t *)out)[0] = h1;
    ((uint32_t *)out)[1] = h2;
    ((uint32_t *)out)[2] = h3;
    ((uint32_t *)out)[3] = h4;
}