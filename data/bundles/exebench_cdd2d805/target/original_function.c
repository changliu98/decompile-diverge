static inline void atomic_retain(volatile int *p)
{
 __sync_fetch_and_add(p, 1);
}