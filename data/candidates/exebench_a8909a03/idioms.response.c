static inline void *put_user_quad(unsigned long addr, void *base)
{
  return (void *)((char *)base + addr);
}