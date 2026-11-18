







static inline void cpuid_count(int op, int count ,int *eax, int *ebx, int *ecx, int *edx){







  __asm__ __volatile__
    ("cpuid": "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx) : "0" (op), "2" (count) : "cc");

}
