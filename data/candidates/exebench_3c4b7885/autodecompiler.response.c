static void set_bit(int bit, unsigned long *map)
{
 map[bit / (8 * sizeof(long))] |= (1UL << (bit % (8 * sizeof(long))));
}