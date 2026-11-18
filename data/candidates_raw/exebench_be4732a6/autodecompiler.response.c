void bitset_set(unsigned long *bitset, int bit)
{
 bitset[bit >> 6] |= ((unsigned long) 1 << (bit & (64 -1)));
}