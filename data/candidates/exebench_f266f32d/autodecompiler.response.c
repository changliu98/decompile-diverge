void getCpuid(unsigned int cpuinfo[4u], unsigned int level)
{

    __asm__ volatile ("xchg %%ebx, %%esi\n\t" "cpuid\n\t" "xchg %%ebx, %%esi\n\t" : "=a"(cpuinfo[0]), "=b"(cpuinfo[1]), "=c"(cpuinfo[2]), "=d"(cpuinfo[3]) : "a"(level), "c"(0));
}