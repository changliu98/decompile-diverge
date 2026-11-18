void set_bit(int bit, unsigned long *map)
{
 unsigned long mask = (1UL << (bit % (sizeof(unsigned long) * 8)));
 unsigned long *ptr = map;
 unsigned long *bmap = &ptr[bit / (sizeof(unsigned long) * 8)];

 *bmap |= mask;
}