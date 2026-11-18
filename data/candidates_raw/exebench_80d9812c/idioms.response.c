static inline int get_lock(void *lock)
{
  return ((int)(*((unsigned long *)lock)) & 1);
}