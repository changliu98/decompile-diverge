void __cdecl cpuid_count(int op, int count, int *eax_0, int *ebx_0, int *ecx_0, int *edx_0)
{
    // __get_cpuid_count executes the CPUID instruction with:
    // EAX = op
    // ECX = count
    // and stores the results in the output registers.
    __get_cpuid_count((unsigned int)op, (unsigned int)count, 
                      (unsigned int *)eax_0, 
                      (unsigned int *)ebx_0, 
                      (unsigned int *)ecx_0, 
                      (unsigned int *)edx_0);
}