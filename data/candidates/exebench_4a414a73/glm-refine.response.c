void __cdecl cpuid_detect(int *sse2, int *sse3)
{
    if (sse2 != NULL)
        *sse2 = 0;
    
    if (sse3 != NULL)
        *sse3 = 0;
}