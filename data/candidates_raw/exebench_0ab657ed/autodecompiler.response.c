void cpuid(int function, int index, unsigned int regs[])
{
    unsigned int eax, ebx, ecx, edx;
    __asm__ __volatile__("pushl %%ebx\n\t"
                         "movl %2,%%eax\n\t"
                         "movl %3,%%ecx\n\t"
                         "cpuid\n\t"
                         "popl %%ebx\n\t"
                         : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
                         : "0" (function), "2" (index));
    regs[0] = eax;
    regs[1] = ebx;
    regs[2] = ecx;
    regs[3] = edx;
}