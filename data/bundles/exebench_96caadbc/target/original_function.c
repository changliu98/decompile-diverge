static inline unsigned long ihk_atomic_add_long_return(long i, long *v) {
        long __i;

        __i = i;
        asm volatile("lock xaddq %0, %1"
                     : "+r" (i), "+m" (*v)
                     : : "memory");
        return i + __i;
}