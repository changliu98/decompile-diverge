static inline void atomic_or_long(unsigned long *v1, unsigned long v2)
{
 asm("" "orq %1, %0" : "+m" (*v1) : "r" (v2));
}