static void *addr_add(void *addr, unsigned int n)
{
  return (void *)((char *)addr + n * sizeof(unsigned long));
}