








static inline void bitfield_set(unsigned long *bits, int bit)
{
 bits[bit / (8 * sizeof(unsigned long))] |= (1UL << (bit % (8 * sizeof(unsigned long))));
}
