int aligned(int val)
{
    return ((val + 0x3F) >> 6) << 6;
}