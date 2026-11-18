
static inline int
atomic_add(volatile int *ptr, int incr)
{
  return __sync_fetch_and_add(ptr, incr);
}
