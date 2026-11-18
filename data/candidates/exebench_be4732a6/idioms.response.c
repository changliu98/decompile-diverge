void bitfield_set(unsigned long *array, int bit)
{
  array[bit / (sizeof(unsigned long) * 8)] |=
    ((unsigned long)1 << (bit % (sizeof(unsigned long) * 8)));
}