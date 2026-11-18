int all_bits_clear(unsigned int value, unsigned int mask)
{
    return (value & mask) == 0;
}