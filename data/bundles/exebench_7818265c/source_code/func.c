
static inline int xchg(volatile int *addr, int newval)
{
 int result;
 asm volatile("lock; xchgl %0, %1" :
   "+m" (*addr), "=a" (result) :
   "1" (newval) :
   "cc");
 return result;
}
