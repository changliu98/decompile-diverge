
static inline void AssignBit(unsigned long* array, int bit, int value)
{
    unsigned long mask = (1L << (bit % (sizeof(long) * 8)));
    if (value)
        array[bit / (sizeof(long) * 8)] |= mask;
    else
        array[bit / (sizeof(long) * 8)] &= ~mask;
}
