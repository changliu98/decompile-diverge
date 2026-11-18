void encipher(uint64_t state[2], const uint8_t key[32])
{
    uint64_t x = state[0];
    uint64_t y = state[1];
    uint64_t z = 0;
    uint64_t sum = 0x9E3779B97F4A7C16;
    uint64_t i;

    for (i = 0; i < 32; i++)
    {
        z += (x & 3) + key[i];
        x += ((y << 4) + key[i]) ^ (z) + (y >> 5);
        z += sum;
        y += ((x << 4) + key[i]) ^ (z) + (x >> 5);
        sum += z;
    }

    state[0] = x;
    state[1] = y;
}