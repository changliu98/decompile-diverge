int func0(uint32_t a, uint32_t b)
{
    int count = 0;
    uint32_t c = a ^ b;
    while (c > 0) {
        count += c & 1;
        c >>= 1;
    }
    return count;
}