static void bnode_link_set_ref(unsigned long *word, unsigned long index)
{
  unsigned long mask = (index * 2 + 1);
  *word = (*word & 1) | mask;
}