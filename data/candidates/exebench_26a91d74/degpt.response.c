void cpuid_detect(int *has_sse2, int *has_sse3)
{
    // Call cpuid with leaf 1 to get CPU feature information
    long cpuid_result = cpuid_Version_info(1);
    
    // If sse2 pointer is valid, extract SSE2 support bit (bit 26 of EDX)
    if (has_sse2 != (int *)0x0) {
        *has_sse2 = *(int *)(cpuid_result + 8) >> 0x1a & 1;
    }
    
    // If sse3 pointer is valid, extract SSE3 support bit (bit 0 of ECX)
    if (has_sse3 != (int *)0x0) {
        *has_sse3 = *(uint *)(cpuid_result + 0xc) & 1;
    }
}