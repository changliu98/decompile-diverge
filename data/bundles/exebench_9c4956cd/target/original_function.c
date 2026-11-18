static inline void cpuid(int op, int *eax, int *ebx, int *ecx, int *edx){







  __asm__ __volatile__
    ("cpuid": "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx) : "a" (op) , "c" (0) : "cc");

}