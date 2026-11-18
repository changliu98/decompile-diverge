static inline unsigned long long get_buddy(unsigned long long handle)
{
  return (handle & ~PAGE_MASK) >> BUDDY_SHIFT;
}