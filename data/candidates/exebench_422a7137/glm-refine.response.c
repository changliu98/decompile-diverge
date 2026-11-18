void __cdecl GetCPUInfo(int *cpu_info, int info_type)
{
    __asm__ __volatile__(
        "cpuid"
        : "=a" (cpu_info[0]),  // Output: EAX/RAX
          "=b" (cpu_info[1]),  // Output: EBX/RBX
          "=c" (cpu_info[2]),  // Output: ECX/RCX
          "=d" (cpu_info[3])   // Output: EDX/RDX
        : "a" (info_type)      // Input: EAX/RAX
    );
}