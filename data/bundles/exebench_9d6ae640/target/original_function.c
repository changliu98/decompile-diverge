static inline void cpuinfo(int code, int *eax, int *ebx, int *ecx, int *edx) {

    __asm__ volatile("cpuid;"
                     : "=a"(*eax), "=b"(*ebx), "=c"(*ecx),
                       "=d"(*edx)
                     : "a"(code)

                     );

}