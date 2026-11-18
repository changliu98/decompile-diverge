void bitfield_set(unsigned long *bits, int bit)
{
    int index = bit / (sizeof(unsigned long) * 8);
    int offset = bit % (sizeof(unsigned long) * 8);
    bits[index] |= 1UL << offset;
}