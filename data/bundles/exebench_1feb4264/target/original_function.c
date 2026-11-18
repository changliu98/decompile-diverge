static inline int atomicCompareAndSwap(int volatile *var, int ov, int nv) {
    int rv; __asm __volatile ("lock; cmpxchgl %2, %1"
        : "=a" (rv), "=m" (*var) : "r" (nv), "0" (ov), "m" (*var) : "cc");
    return rv;
  }