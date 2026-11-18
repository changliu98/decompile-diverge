void cpuid_detect(int *has_sse, int *has_sse2)
{
    int eax, ebx, ecx, edx;

    __asm__ __volatile__("cpuid" : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx) : "a" (1));

    if (has_sse) *has_sse = (edx & (1 << 25)) != 0;
    if (has_sse2) *has_sse2 = (edx & (1 << 26)) != 0;
}