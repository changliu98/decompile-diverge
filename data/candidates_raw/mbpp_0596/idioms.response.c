static unsigned long get_tuple_size(void *tuple, unsigned long size)
{
  unsigned long total_size = 0;
  for (unsigned long i = 0; i < size; i++)
  {
    total_size += sizeof(void *);
  }
  return total_size;
}