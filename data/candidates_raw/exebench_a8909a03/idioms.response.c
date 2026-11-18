static inline void *reloc(unsigned long addr, void *base)
{
  return (void *)((char *)base + addr);
}