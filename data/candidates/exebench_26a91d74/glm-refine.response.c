void __cdecl cpuid_detect(int *sse2, int *sse3)
{
    int cpu_info[4];
    __cpuid(cpu_info, 1);

    // cpu_info[3] corresponds to EDX
    // cpu_info[2] corresponds to ECX

    if (sse2)
        *sse2 = (cpu_info[3] >> 26) & 1; // Bit 26 of EDX indicates SSE2 support

    if (sse3)
        *sse3 = cpu_info[2] & 1;         // Bit 0 of ECX indicates SSE3 support
}