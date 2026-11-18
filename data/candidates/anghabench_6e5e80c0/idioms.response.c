static void *adjust_stack_addr(void *addr, unsigned int n)
{
  return (void *)((char *)addr + n * sizeof(unsigned long));
}