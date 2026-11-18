static inline int atomicDecrement(int volatile *var) {
    int ov; __asm__ __volatile__ ("lock; xaddl %0, %1"
         : "=r" (ov), "=m" (*var) : "0" (-1), "m" (*var) : "cc" );
    return ov - 1;
  }