
static inline void atomic_inc(volatile int *a) {
   __asm(
        "lock; incl %0"
        : "=m" (*a)
   );
}
