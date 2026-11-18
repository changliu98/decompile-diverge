
static __inline void cpuid(int op, int *eax, int *ebx, int *ecx, int *edx){
# 127 "common_x86_64.h"
        __asm__ __volatile__("cpuid"
        : "=a" (*eax),
        "=b" (*ebx),
        "=c" (*ecx),
        "=d" (*edx)
        : "0" (op));

}
