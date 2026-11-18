void set_bit(unsigned char *map, size_t bit)
{
 unsigned char mask = 1 << (7 - (bit % 8));
 map[bit / 8] |= mask;
}