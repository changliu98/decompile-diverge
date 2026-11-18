void
AssignBit(
    unsigned long *bit_array,
    int bit,
    int value
    )
{
    unsigned long mask;

    mask = 1L << (bit & 0x3f);
    if (value)
 bit_array[bit >> 6] |= mask;
    else
 bit_array[bit >> 6] &= ~mask;
}