static void set_bit(unsigned long *word, unsigned long index)
{
  unsigned long mask = (index * 2 + 1);
  *word = (*word & 1) | mask;
}