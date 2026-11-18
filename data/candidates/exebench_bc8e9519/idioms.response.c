static void generic_set_bit(int nr, unsigned long *word)
{
  word[nr / (sizeof(unsigned long) * 8)] |= (1UL << (nr % (sizeof(unsigned long) * 8)));
}