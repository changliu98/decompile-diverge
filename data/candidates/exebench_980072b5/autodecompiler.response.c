static void set_bit(int bit, unsigned long *map)
{
 unsigned long mask = (1UL << (bit % 64));
 unsigned long *p = map + (bit / 64);
 *p |= mask;
}