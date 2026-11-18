static __inline__ int trylock (volatile int* lock) {
    char oldval;
    __asm__ __volatile__
        (
         "xchgb %b0,%1"
         :"=q" (oldval),
          "=m" (*lock)
         :"0" (1)
         : "memory");
    return oldval == 0;
}