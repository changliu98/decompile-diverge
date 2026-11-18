void
cpuid_detect (int * sse2, int * sse3)
{
    int a, b, c, d;
    __asm__ __volatile__ ( "xchgl %%ebx, %1    \n\t" "cpuid              \n\t" "xchgl %%ebx, %1    \n\t" : "=a" (a), "=r" (b), "=c" (c), "=d" (d) : "a" (1) : "cc");

    if (sse2)
        *sse2 = (d >> 26) & 1;
    if (sse3)
        *sse3 = c & 1;
}