void cpuid_detect(int *sse2, int *sse3)
{
    int eax = 1;
    int ebx, ecx, edx;
    int *info = cpuid_Version_info(eax);

    eax = info[0];
    ebx = info[1];
    ecx = info[2];
    edx = info[3];

    if (sse2)
        *sse2 = (edx & (1 << 26)) != 0;
    if (sse3)
        *sse3 = (ecx & (1 << 0)) != 0;
}