void set_bit(int bit, unsigned long *map)
{
 map[((bit) / (sizeof(long) * 8))] |= (1UL << ((bit) % (sizeof(long) * 8)));
}