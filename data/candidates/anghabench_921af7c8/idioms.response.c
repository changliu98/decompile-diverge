static inline unsigned long long handle_to_chunks(unsigned long long handle)
{
  return (handle & ~PAGE_MASK) >> BUDDY_SHIFT;
}