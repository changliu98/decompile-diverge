char *
func0(uint32_t x)
{
    x ^= x >> 1;
    x ^= x >> 2;
    x ^= x >> 4;
    x ^= x >> 8;
    x ^= x >> 16;

    if (x & 1)
        return "Odd Parity";
    else
        return "Even Parity";
}