void bitclear(int i, unsigned long *array)
{
  array[i / (sizeof(unsigned long) * 8)] &= ~(1UL << (i % (sizeof(unsigned long) * 8)));
}