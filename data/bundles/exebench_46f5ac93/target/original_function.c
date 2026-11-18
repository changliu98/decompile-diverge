static __inline__ void spin_unlock (volatile int* lock) {
 __asm__ __volatile__
        ("movb $0,%0"
         :"=m" (*lock) : : "memory");
}