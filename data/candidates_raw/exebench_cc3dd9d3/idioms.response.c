void set_bit(unsigned long *array, int bit, int value)
{
  unsigned long mask = 1ul << (bit & 63);
  array[bit / 64] = (value == 0) ? (array[bit / 64] & ~mask) : (array[bit / 64] | mask);
}