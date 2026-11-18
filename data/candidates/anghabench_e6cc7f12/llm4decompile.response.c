uint64_t aligned(uint64_t val)
{
    return ((val + 63) >> 6) << 6;
}